package redes;

import java.io.IOException;
import java.util.Random;

public class Enlace {

    private static Fisica fis;
    private static String palavra;

    public Enlace() throws IOException {
        fis = new Fisica();
    }

    //GERADOR DE PALAVRAS DE TAMANHO 4
    public static String gerador() {
        Random ale = new Random();
        //int n;
        String palavra = "" + ale.nextInt(2);
        for (int i = 0; i < 3; i++) {
            palavra += ale.nextInt(2);
        }
        return palavra;
    }

    //GERADOR DA MENSAGEM TOTAL
    public static String gerarPalavra(int c) {
        String palavraCompleta = gerador();
        if (c == 1) {
            palavraCompleta = fis.codificador(palavraCompleta);
        }
        //System.out.println(palavraCompleta);
        for (int i = 0; i < 2; i++) {
            String p = gerador();
            if (c == 1) {
                p = fis.codificador(p);
            }
            //System.out.println(p);
            palavraCompleta = palavraCompleta + p;
        }
        //System.out.println(palavraCompleta);
        return palavraCompleta;
    }

    public static String getPalavra() {
        return palavra;
    }

    //CODIGOS DE DETECCAOO DE ERRO
    //BITS DE PARIDADE
    public static void detectarBitDeParidadePar(String pal) {
        int cont = 0;
        for (int i = 0; i < pal.length(); i++) {
            if (pal.charAt(i) == '1') {
                cont++;
            }
        }
        if (cont % 2 == 0) {
            pal += '0';
            palavra = pal;
        } else {
            pal += '1';
            palavra = pal;
        }

    }

    static void detectarErro(String pal) {
        int cont = 0;
        for (int i = 0; i < pal.length(); i++) {
            if (pal.charAt(i) == '1') {
                cont++;
            }
        }
        if (cont % 2 == 0) {
            System.out.println("Paridade: SEM ERRO");
        } else {
            System.out.println("Paridade: ERRO");
        }
    }

    // CHECKSUM
    public static String[] wordBreaker(String dado) {
        int numSegmentos;
        int flag = 0;
        int tamanho = dado.length();

        if (tamanho % 5 == 0) {
            flag = 1;
            numSegmentos = tamanho / 5;
        } else {
            flag = 0;
            numSegmentos = tamanho / 4;
        }
        String[] segmentos = new String[numSegmentos];

        for (int i = 0, j = 0; i < tamanho; i += (4 + flag), j++) {
            String word = "";
            for (int k = i; k < i + (4 + flag) && k < tamanho; k++) {
                word = word + dado.charAt(k);

            }

            segmentos[j] = word;
        }

        return segmentos;

    }

    public static String resolveChecksum(String word) {
        int numSegmentos;
        int flag = 0;
        int tamanho = word.length();

        if (tamanho % 5 == 0) {
            flag = 1;
            numSegmentos = tamanho / 5;
        } else {
            flag = 0;
            numSegmentos = tamanho / 4;
        }
        String[] segmentos = new String[numSegmentos];

        for (int i = 0, j = 0; i < tamanho; i += (4 + flag), j++) {
            String word1 = "";
            for (int k = i; k < i + (4 + flag) && k < tamanho; k++) {
                word1 = word1 + word.charAt(k);

            }

            segmentos[j] = word1;
        }

        int soma = 0;
        for (int i = 0; i < numSegmentos; i++) {
            soma += (Integer.parseInt(segmentos[i], 2));
        }

        String checksum = Integer.toBinaryString(soma);
        String invertido = "";
        for (int i = 0; i < checksum.length(); i++) {
            if (checksum.charAt(i) == '0') {
                invertido += '1';
            } else {
                invertido += '0';
            }
        }
        for (int i = 0; i < invertido.length(); i++) {
            if (invertido.charAt(i) != '0') {
                return null;
            }
        }
        String ret = "";
        for (int i = 0; i < numSegmentos - 1; i++) {
            ret += segmentos[i];
        }
        return ret;

    }

    public static String criaChecksum(String[] word) {
        int tamanho = word.length;

        int soma = 0;
        for (int i = 0; i < tamanho; i++) {
            soma += (Integer.parseInt(word[i], 2));
        }

        String checksum = Integer.toBinaryString(soma);
        String f = "";
        String checksumInvertido = "";
        for (int k = 0; k < checksum.length(); k++) {
            if (checksum.charAt(k) == '0') {
                checksumInvertido += '1';
            } else {
                checksumInvertido += '0';
            }
        }
        if (checksumInvertido.length() > word[0].length()) {
            checksumInvertido = checksumInvertido.substring(1, checksumInvertido.length());
        }
        for (int i = 0; i < word.length; i++) {
            f += word[i];
        }

        for (int k = 0; k < checksumInvertido.length(); k++) {
            f += checksumInvertido.charAt(k);
        }

        return f;

    }
}
