import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void get(StringBuilder sb) {

        if (sb.indexOf("<title>") != -1) {
            String text = sb.substring(sb.indexOf("<title>") + 7, sb.indexOf("</title>"));
            System.out.println(text);
        }
        if (sb.indexOf("<th>") != -1) {
            String text = sb.substring(sb.indexOf("<th>") + 4, sb.indexOf("</th>"));
            String text2 = sb.substring(sb.lastIndexOf("<th>") + 4, sb.lastIndexOf("</th>"));
            System.out.println(text+"\t\t\t"+text2);
        }

        if (sb.indexOf("<span class=\"text\">") != -1) {
            String text1 = sb.substring(sb.indexOf("<span class=\"text\">") + 19, sb.indexOf("<span class=\"text\">") + 39);
            String text2 = sb.substring(24260 + 5, 24260 +11);
            System.out.println(text1+"\t\t\t\t\t"+text2);

        }
        if (sb.lastIndexOf("<span class=\"text\">") != -1) {
            String text2 = sb.substring(sb.lastIndexOf("<span class=\"text\">") + 19, sb.lastIndexOf("<span class=\"text\">") + 36);
            String text1 = sb.substring(33798 + 5, 33798 +11);
            System.out.println(text2+"\t\t\t\t\t\t"+text1);

        }
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        Socket clientSocket;
        InetAddress inetAddress;
        String server;
        server = "www.nbrb.by";
        BufferedReader buffer = null;
        PrintWriter printer = null;
        StringBuilder sb= new StringBuilder();

        try {
            inetAddress = InetAddress.getByName(server);
            clientSocket = new Socket(inetAddress, 80);
            buffer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            printer = new PrintWriter(new BufferedWriter((new OutputStreamWriter(clientSocket.getOutputStream()))), true);
            printer.println("GET " +"/statistics/rates/ratesDaily.asp"+ " HTTP/1.1\r\nHost: " + server +"\r\n\r\n");
            String s;
            System.out.println("Добро пожаловать в наш банк");
            System.out.println("Подождите, идёт запрос на получение курса валюты...");
            while((s = buffer.readLine())!=null) {
                sb.append(s);
                sb.append("\n");
            }
        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
            return;
        }
        System.out.println();
        get(sb);
        System.out.println();
        System.out.println("Спасибо,что выбрали наш банк !!!");


    }
}
