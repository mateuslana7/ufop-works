package redes;
 
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;
 
public class Servidor {
    public Servidor() throws IOException {
    
    int porta = 12345;    
    ServerSocket servidor = new ServerSocket(porta);
    System.out.println("Porta "+porta+" aberta!");
    Socket cliente = servidor.accept();
    System.out.println("Nova conexao com o cliente " + cliente.getInetAddress().getHostAddress());
    Scanner entrada = new Scanner(cliente.getInputStream());
    while (entrada.hasNextLine()) {
        String palavraRecebida = entrada.nextLine();
        System.out.println(palavraRecebida);
        System.out.println("Palavra recebida!");
        Enlace.detectarErro(palavraRecebida);
        if (Enlace.resolveChecksum(palavraRecebida) == null) System.out.println("Checksum: ERRO");
    } 
    entrada.close();
    servidor.close();
    }
    
 }