import java.io.*;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException, InterruptedException {
        String filePath = "C:\\Users\\joeyd\\Downloads\\test.txt";
        
        try {
            File file = new File(filePath);
            if (file.exists()) {
                System.out.println("File exists at: " + filePath);
            } else {
                System.out.println("File does not exist at: " + filePath);
                return;
            }
            System.out.println("ENTERING C PROGRAM FROM JAVA");
            System.out.println("----------------------------");

            // 1. Run C program
            Process proc = Runtime.getRuntime().exec("./Second");

            // 2. Set up input and output streams for communication with the C program
            InputStream in = proc.getInputStream();
            OutputStream out = proc.getOutputStream();
            Scanner userInput = new Scanner(System.in);

            // 3. Continuously read input from the user and send to C program
            while (true) {
                System.out.print("Enter row and column for the move (e.g., '0 1') or 'exit' to quit: ");
                String input = userInput.nextLine();

                // Send input to the C program
                writeToProc(out, input + "\n");

                // If the user typed 'exit', break the loop
                if (input.equals("exit")) {
                    break;
                }

                // Read response from the C program (updated board and messages)
                readFromProc(in);
            }

            // Close the streams and process when done
            out.close();
            in.close();
            proc.destroy();
            userInput.close();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    // Write message to process
    public static void writeToProc(OutputStream out, String msg) throws IOException {
        byte[] buff = msg.getBytes("UTF-8");
        out.write(buff);
        out.flush();
        System.out.println("Sent to C program: " + msg);
    }

    // Read stdin of process
    public static void readFromProc(InputStream in) throws IOException {
        byte[] buff = new byte[256];
        int read = in.read(buff);
        if (read != -1) {
            String response = new String(buff, 0, read, "UTF-8");
            System.out.println("C program says: " + response);
        }
    }
}

