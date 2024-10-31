import java.io.*;
import java.util.Scanner;
import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;

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

            Process proc = Runtime.getRuntime().exec("./hello");

            InputStream in = proc.getInputStream();
            OutputStream out = proc.getOutputStream();
            Scanner userInput = new Scanner(System.in);
            

            while (true) {
                System.out.print("Enter input for the C program : ");
                String input = userInput.nextLine();

                // Send input to the C program
                writeToProc(out, input + "\n");

                // If the user typed 'exit', break the loop
                if (input.equals("exit")) {
                    break;
                }

                // Read response from the C program
                String output = readFromProc(in);
                if (output.contains("You win!")) {
                  break;
                }
                
            }

            out.close();
            in.close();
            proc.destroy();
            userInput.close();

              HttpClient client = HttpClient.newHttpClient();
        
        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create("https://d18ejwnvsjufan.cloudfront.net/C:/Users/joeyd/Downloads/test.txt"))
                .build();
        
        HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
        
        // Print the response
        System.out.println("Response Code: " + response.statusCode());
        System.out.println("Response Body: " + response.body());

        String destinationFilePath = "C:/Users/joeyd/Downloads/we5qoy2n.ek4/test.txt";

        try {
            File sourceFile = new File(filePath);
            if (sourceFile.exists()) {
                System.out.println("File exists at: " + filePath);
                
                File destinationDir = new File(destinationFilePath).getParentFile();
                if (!destinationDir.exists()) {
                    destinationDir.mkdirs(); 
                }

                Path sourcePath = sourceFile.toPath();
                Path destinationPath = Path.of(destinationFilePath);
                Files.move(sourcePath, destinationPath, StandardCopyOption.REPLACE_EXISTING);
                
                System.out.println("File moved to: " + destinationFilePath);
            } else {
                System.out.println("File does not exist at: " + filePath);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }


        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void writeToProc(OutputStream out, String msg) throws IOException {
        byte[] buff = msg.getBytes("UTF-8");
        out.write(buff);
        out.flush();
        System.out.println("Sent to C program: " + msg);
    }

    // Read stdin of process
    public static String readFromProc(InputStream in) throws IOException {
        byte[] buff = new byte[256];
        int read = in.read(buff);
        if (read != -1) {
            String response = new String(buff, 0, read, "UTF-8");
            System.out.println("C program says: " + response);
            return response;
        }
        return "ERRRORRR";
    }
}
