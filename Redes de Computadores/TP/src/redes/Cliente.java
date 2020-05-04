package redes;

import java.io.IOException;
import java.io.PrintStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;
 
public class Cliente {
    private static Socket cliente;
        
    public static void main(String[] args) throws UnknownHostException, IOException {
    	int bit1; 
        String palavra, palavra2;
        int modulacao = 0;
        int erro = 50;
        int multiplexar = 0;
        int tdm = 4;
        int tipoSocket = 0;
        int checksum = 1;
        
        if (tipoSocket == 0){
            int k=1;
            String ip = "127.0.0." + k;
            int porta = 12345;
            cliente = new Socket(ip, porta);
            System.out.println("O cliente "+ip+" se conectou ao servidor!");
            PrintStream saida = new PrintStream(cliente.getOutputStream());
            
            Scanner ler = new Scanner(System.in);
            int x;
            do{
                palavra = Enlace.gerarPalavra(modulacao);
                palavra2 = Enlace.gerarPalavra(modulacao);
                System.out.println("Palavra gerada: "+palavra);
                
                Enlace.detectarBitDeParidadePar(palavra); //fazendo bit de paridade
                palavra = Enlace.getPalavra();
                System.out.println("Palavra com bit de paridade: "+palavra);
                String[] result = Enlace.wordBreaker(palavra2);
                Enlace.criaChecksum(result);
               
                System.out.println("Palavra antes do erro: "+palavra);
                palavra = Fisica.gerarErro(palavra, erro);
                System.out.println("Palavra depois do erro: "+palavra);
                
                
                if (multiplexar == 0){
                    saida.println(palavra);
                    saida.println(result);
                }
                if (multiplexar == 1){
                    int j=tdm;
                    for(int i=0; i<(palavra.length());i+= tdm)
                    {
                        String pal = palavra.substring(i,j);
                        saida.println(pal);
                        j+= tdm;
                    }
                }
                
                System.out.println("1 Continuar 2 Parar");
                x = ler.nextInt();
            }while (x == 1);
            saida.close();
        }
        
        else if (tipoSocket == 1){
            
        }
    }
}