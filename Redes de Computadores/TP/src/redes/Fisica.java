package redes;

import java.io.IOException;
import java.util.Random;


public class Fisica {
    private Servidor servidor;
    private Cliente cliente;
    
    public Fisica() throws IOException{
        servidor = new Servidor();
        cliente = new Cliente();
    }
    
    public static String codificador(String palavra){ 
        String nova;
        nova = "0";
        switch(palavra){
            case "0000":
                nova = "11110";
                break;
            case "0001":
                nova = "01001";
                break;
            case "0010":
                nova = "10100";
                break;
            case "0011":
                nova = "10101";
                break;
            case "0100":
                nova = "01010";
                break;
            case "0101":
                nova = "01011";
                break;
            case "0111":
                nova = "01111";
                break;
            case "0110":
                nova = "01110";
                break;
            case "1000":
                nova = "10010";
                break;
            case "1001":
                nova = "10011";
                break;
            case "1010":
                nova = "10110";
                break;
            case "1011":
                nova = "10111";
                break;
            case "1100":
                nova = "11010";
                break;
            case "1101":
                nova = "11011";
                break;
            case "1110":
                nova = "11100";
                break;
            case "1111":
                nova = "11101";
                break;  
        }    
        return nova;
    }
    
    static String gerarErro(String palavra, int erro) 
    {
        Random ale = new Random();
        String nova = "0";
        for(int i=0; i< palavra.length();i++)
        {
            if (ale.nextInt(100) < erro)
            {
                if (palavra.charAt(i) == '0')
                {
                    palavra = palavra.substring(0,i)+ '1' +palavra.substring(i+1);
                } 
                else if (palavra.charAt(i) == '1')
                {
                    palavra = palavra.substring(0,i)+ '0' +palavra.substring(i+1);
                }
            } 
        }
        return palavra;
    }
}