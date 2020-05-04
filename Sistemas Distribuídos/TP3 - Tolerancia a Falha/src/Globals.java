import java.io.IOException;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.util.List;

public class Globals {
	public static String servidorPrimario = "200.239.139.116";
	public static String servidorBackup = "200.239.139.122";
	
	public static final int atraso = 500;
	public static final int tamMaxPonto = 15;
	
	public static String servidorSecundario;

	public static final int maxAtualizacoes = 30;
	public static final int PORTA = 8080;

	public static final int MUDANCA = 10;
	public static final int NOVOCLIENTE = 20;
	public static final int COPIA = 30;
	public static final int ENVIAMUDANCA = 40;

	public static final int dimensaoX = 1680;
	public static final int dimensaoY = 1050;

	public static final int NOVO = 0;
	public static final int REMOVE = 1;
	public static final int ATUALIZA = 2;
    public static final int COR = 5;
	
    //TESTA SE EXISTE CONEXAO 
	public static boolean ping() 
    {
		try 
        {
			InetAddress ping = InetAddress.getByName("200.239.139.113");
			return ping.isReachable(10);
		} catch (IOException e) {
//			e.printStackTrace();
			return false;
		}
	}
    
    
	public static void enviarMensagem(String origem, String destino, int tipo, int port, List<Ponto> pontos, List<Atualizacao> filaAlteracoes, Atualizacao atualizacao)
	{
		try 
		{
			Socket destinatario = new Socket(destino, port);

			Mensagem msg = new Mensagem();
			msg.setTipo(tipo);
			msg.setOrigem(origem);
			msg.setDestino(destino);
			msg.setPontos(pontos);
			msg.setListaAtualizacoes(filaAlteracoes);
			msg.setAtualizacao(atualizacao);
			ObjectOutputStream out = new ObjectOutputStream(destinatario.getOutputStream());
			out.writeObject(msg);
			out.flush();
			out.close();

			destinatario.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void enviarMensagemNovoCliente(String origem, String destino, int tipo, int port, List<Ponto> pontos) {
		enviarMensagem(origem, destino, tipo, port, pontos, null, null);
	}

	public static void enviarMensagem(String origem, String destino, int tipo, int port, List<Ponto> pontos, List<Atualizacao> filaAlteracoes) {
		enviarMensagem(origem, destino, tipo, port, pontos, filaAlteracoes, null);
	}

	public static void enviarMensagem(String origem, String destino, int tipo, int port, List<Atualizacao> alteracoes){
		enviarMensagem(origem, destino, tipo, port, null, alteracoes, null);
	}

	// alteracao
	public static void enviarMensagem(String origem, String destino, int tipo, int port, Atualizacao atualizacao) {
		enviarMensagem(origem, destino, tipo, port, null, null, atualizacao);
	}
	
}
