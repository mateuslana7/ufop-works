import java.awt.SecondaryLoop;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class Server {
	public static ArrayList<String> filosofos;
	public static ServerSocket serverSocket;
	public static final int porta = 7878;
	public final static int quantFilosofos = 5;

	//INICIA O SERVIDOR GLOBAL E FICA AGUARDANDO CONEXAO DOS FILOSOFOS
	public static void main(String args[]) 
	{
		try 
		{
			filosofos = new ArrayList<>();

			serverSocket = new ServerSocket(porta);
			
			new Thread() 
			{
				@Override
				public void run() 
				{
					aguardaConexao();
				}
			}.start();// TODO

		} 
		catch (Exception e) 
		{
		}
	}

	private static void aguardaConexao() 
	{
		while (true) 
		{
			try 
			{
				Socket clientSocket = serverSocket.accept();
				ObjectInputStream in = new ObjectInputStream(clientSocket.getInputStream());
				
				//LE AS MENSAGENS DOS FILOSOFOS E VAI ADICIONANDO ELES NA LISTA
				try 
				{
					MensagemF msg = (MensagemF) in.readObject();
					System.out.println(msg.getId()+" conectou");
					if (msg.getTipo() == MensagemF.LOGIN) 
					{
						filosofos.add(msg.getId());
					}
				} catch (Exception e) 
				{
				}

			} 
			catch (Exception e) 
			{
				System.out.println("Server Stopped.");
				return;
			}
			
			for(int i = 0; i < filosofos.size(); i++)
			{
				System.out.println(i+":"+filosofos.get(i));		
			}
			
			//VERIFICA A QUANTIDADE DE FILOSOFOS E DEFINE OS VIZINHOS DE CADA UM
			if (filosofos.size() == quantFilosofos) 
			{
				for (int i = 0; i < filosofos.size(); i++) 
				{
					ArrayList<String> vizinhos = new ArrayList<>();
					try 
					{
						if (i == 0) 
						{
							vizinhos.add(filosofos.get(filosofos.size() - 1));
							vizinhos.add(filosofos.get(i + 1));
						} 
						else if (i == filosofos.size() - 1) 
						{
							vizinhos.add(filosofos.get(i - 1 ));
							vizinhos.add(filosofos.get(0));
						} 
						else
						{	
							vizinhos.add(filosofos.get(i - 1));
							vizinhos.add(filosofos.get(i+1));
						}
						//ENVIA MENSAGEM PARA CADA CLIENTE INICIAR
						enviarMensagem(MensagemF.INICIAR, filosofos.get(i), porta, vizinhos);
						System.out.println("INICIAR");
					} 
					catch (Exception e) 
					{
						e.printStackTrace();
					}
				}
				System.exit(0);
			}
		}
	}

	private static void enviarMensagem(int tipo, String ip, int porta, ArrayList<String> vizinhos) throws IOException 
	{
		try 
		{
			Socket vizinho = new Socket(ip, porta);

			MensagemF msg = new MensagemF();
			msg.setTipo(tipo);
			msg.setId(vizinho.getLocalAddress().getHostAddress());
			msg.setVizinhos(vizinhos);
			ObjectOutputStream out = new ObjectOutputStream(vizinho.getOutputStream());
			out.writeObject(msg);
			out.flush();
			out.close();

			vizinho.close();
		} 
		catch (Exception e) 
		{
		}
	}
}
