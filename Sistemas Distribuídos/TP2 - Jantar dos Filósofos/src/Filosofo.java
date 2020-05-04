import java.awt.SecondaryLoop;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Map;
import java.util.Queue;
import java.util.concurrent.LinkedBlockingQueue;

public class Filosofo {
	private enum State {
		PENSANDO, COM_FOME, COMENDO
	}

	private static State estadoAtual;
	private static Timestamp meuTempo;
	private static Queue<String> filaPrioridade;
	private static int contadorResp;
	private static ArrayList<String> vizinhos;
	private static ServerSocket serverSocket;
	private static int porta = 7878;
	private static Filosofo filosofo;
	private static int quantComeu;
	private static boolean permissaoComer = true;
	private static boolean iniciar = false;
	private static int quantMax = 10;

	//TENTA CHAMAR O METODO PARA INSTANCIAR O CLIENTE
	public static void main(String args[]) 
	{
		try 
		{
			getInstance();
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
	}

	//INSTANCIA O CLIENTE
	public static synchronized Filosofo getInstance() throws IOException 
	{
		if (filosofo == null)
		{
			try 
			{
				filosofo = new Filosofo();
			} 
			catch (InterruptedException e) 
			{
				e.printStackTrace();
			}
		}
		return filosofo;
	}

	//CONSTRUTOR 
	public Filosofo() throws IOException, InterruptedException 
	{
		try 
		{
			enviarMensagem(MensagemF.LOGIN, "200.239.138.239");//IP DO SERVIDOR GLOBAL
			filaPrioridade = new LinkedBlockingQueue<>();
			quantComeu = 0;
			serverSocket = new ServerSocket(porta);
			
			//CRIA E DA START EM UMA THREAD QUE FICA ESPERANDO RESPOSTA DO SERVIDOR GLOBAL
			new Thread() 
			{
				@Override
				public void run() 
				{
					escutaMensagem();
				}
			}.start();// TODO
			
			while (true) 
			{
				System.out.println(" ");
				
				//VERIFICA SE TODOS OS FILOSOFOS ESTAO "PRONTOS" PARA INICIAR
				if (iniciar)
				{	
					//ENQUANTO NAO ATINGIR O LIMITE ESTABELECIDO E TIVER PERMISSAO PARA COMER
					while (permissaoComer && quantComeu < quantMax) 
					{
						System.out.println("PENSANDO");
						estadoAtual = State.PENSANDO;
						Thread.sleep(1500);
						System.out.println("COM FOME");
						estadoAtual = State.COM_FOME;
						
						//SOLICITA OS VIZINHOS PARA COMER E REGISTRA O TEMPO DO PEDIDO 
						meuTempo = new Timestamp(System.currentTimeMillis());
						System.out.println("SOLICITANDO VIZINHO 1");
						enviarMensagem(MensagemF.REQUISICAO, this.vizinhos.get(0));
						System.out.println("SOLICITANDO VIZINHO 2");
						enviarMensagem(MensagemF.REQUISICAO, this.vizinhos.get(1));
						
						//SE NAO RECEBEU RESPOSTAS DOS DOIS VIZINHOS FICA ESPERANDO
						if (contadorResp < 2) 
						{
							synchronized (this) 
							{
								System.out.println("ESPERANDO...");
								this.wait();
							}
						}
						
						//ALTERA O ESTADO PARA "COMENDO" E INCREMENTA O CONTADOR
						System.out.println("COMENDO");
						estadoAtual = State.COMENDO;
						Thread.sleep(1000);
						quantComeu++;
						
						//REINICIALIZA O CONTADOR DE RESPOSTAS
						synchronized (this) 
						{
							contadorResp = 0;
						}
						
						//ENQUANTO MINHA FILA DE PRIORIDADE NAO ESTIVER VAZIA EU ENVIO RESPOSTAS
						while (!filaPrioridade.isEmpty()) 
						{
							enviarMensagem(MensagemF.RESPOSTA, filaPrioridade.poll());
						}

					}
					
					//CASO EU ATINJA O MAXIMO ESTIPULADO EU TERMINO A EXECUCAO E MANDO MEU VIZINHO 1 TERMINAR
					if (permissaoComer == false || quantComeu == quantMax) 
					{
						String ipMaquina = "";
						enviarMensagem(MensagemF.FINALIZA, this.vizinhos.get(1));
						try {
					           ipMaquina = InetAddress.getLocalHost().getHostAddress();
					    } 
						 catch (Exception e) {
					    }
						enviarMensagem(MensagemF.FINALIZA, ipMaquina);
					}
				}
			}

		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
	}

	public void escutaMensagem() 
	{
		while (true) 
		{
			try 
			{
				Socket clientSocket = serverSocket.accept();

				ObjectInputStream in = new ObjectInputStream(clientSocket.getInputStream());
				try 
				{
					MensagemF msg = (MensagemF) in.readObject();

					System.out.println("Recebendo " + msg.getTipo() + " da porta: " + msg.getId());
					
					//TRATAMENTO PARA CADA TIPO DE MENSAGEM QUE EH RECEBIDO
					switch (msg.getTipo()) 
					{
						case MensagemF.RESPOSTA:
							contadorResp++;
							if (contadorResp == 2) 
							{
								synchronized (this) 
								{
									this.notify();
								}
							}
							break;
						case MensagemF.REQUISICAO:
							if (estadoAtual == State.COM_FOME) 
							{
								if (meuTempo.getTime() <= msg.getTimestamp().getTime()) 
								{
									filaPrioridade.add(msg.getId());
								} 
								else 
								{
									enviarMensagem(MensagemF.RESPOSTA, msg.getId());
								}
							} 
							else 
							{
								if (estadoAtual == State.PENSANDO)
									enviarMensagem(MensagemF.RESPOSTA, msg.getId());
								else
									filaPrioridade.add(msg.getId());
							}
							break;
						case MensagemF.WAKEUP:
							synchronized (this) 
							{
								this.notify();
							}
							break;
						case MensagemF.FINALIZA:
							estadoAtual = State.PENSANDO;
							System.out.println("Quantidade de vezes que esse filosofo comeu: " + quantComeu);
							permissaoComer = false;
							System.exit(0);
							break;
						case MensagemF.INICIAR:
							System.out.println("INICIANDO O PROGRAMA");
							vizinhos = msg.getVizinhos();
							System.out.println("VIZINHOS\n\t1: " + vizinhos.get(0));
							System.out.println("VIZINHOS\n\t1: " + vizinhos.get(1));
							iniciar = true;
						default:
							break;
					}
				} 
				catch (Exception e) 
				{
					e.printStackTrace();
				}
				clientSocket.close();
				in.close();
			} 
			catch (IOException e) 
			{
				System.out.println("Server Stopped.");
				return;
			}
		}
	}
	
	private void enviarMensagem(int tipo, String ip) throws IOException 
	{
		enviarMensagem(tipo, ip, Server.porta);
	}

	private void enviarMensagem(int tipo, String ip, int porta) throws IOException 
	{
		//ENVIA A MENSAGEM PARA O VIZINHO ESPECIFICADO PASSANDO TIPO,IP,PORTA E MEU TEMPO
		try 
		{
			Socket vizinho = new Socket(ip, porta);

			MensagemF msg = new MensagemF();
			msg.setTipo(tipo);
			msg.setId(vizinho.getLocalAddress().getHostAddress());
			if (tipo == MensagemF.REQUISICAO) 
			{
				msg.setTimestamp(meuTempo);
			}

			ObjectOutputStream out = new ObjectOutputStream(vizinho.getOutputStream());
			out.writeObject(msg);
			out.flush();
			out.close();

			vizinho.close();
		} 
		catch (Exception e) 
		{
			synchronized (this) 
			{
				contadorResp++;
			}
		}
	}
}
