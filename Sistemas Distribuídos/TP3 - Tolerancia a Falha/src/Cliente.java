import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;
import java.util.spi.TimeZoneNameProvider;

public class Cliente {

	private static ServerSocket servidor;
	public static List<Ponto> listaPontos;
	public static Frame tela;
	public static int id = 0;
	public static String meuIP = "";

	public static void main(String[] args) throws Exception {

		tela = new Frame();

		listaPontos = new LinkedList<Ponto>();
		new Cliente().executa();
	}

	public void executa() throws IOException 
    {
		Cliente.servidor = new ServerSocket(Globals.PORTA);
		servidor.getInetAddress();
		meuIP = InetAddress.getLocalHost().toString().replaceAll(".*/", "");
		System.out.println("CLIENTE ABERTO!");
        
		new Thread() {
			@Override
			public void run() {
				listenServidor();
			}
		}.start();
        
		new Thread() {
			@Override
			public void run() {
				requesitarAlteracoes();
			}
		}.start();

		new Thread() {
			@Override
			public void run() {
				repintar();
			}
		}.start();
	}

	public static void requesitarAlteracoes() 
    {
		while (true) 
        {
			Random r = new Random();
			int atualizacoes = r.nextInt(Globals.maxAtualizacoes);
			Atualizacao a = new Atualizacao();
			a.setQuantidade(atualizacoes);
			a.setOrigem(meuIP);
			a.setId(meuIP + "_" + id);
			boolean passou = false;
            
			try{
				Thread.sleep(5*Globals.atraso);
			} 
            catch (Exception e) {
			}
            
            //ENVIA AS ATUALIZACOES AO SERVIDOR PRINCIPAL
			try 
            {
				Globals.enviarMensagem(meuIP, Globals.servidorPrimario, Globals.MUDANCA, Globals.PORTA, a);
				passou = true;
			} 
            catch (Exception e) {
                System.out.println("SERVIDOR PRINCIPAL CAIU!");
				continue;
			}
            
            //ENVIA AS MUDANCAS AO SERVIDOR SECUNDARIO
			try 
            {
				Globals.enviarMensagem(meuIP, Globals.servidorBackup, Globals.MUDANCA, Globals.PORTA, a);
				passou = true;
			} 
            catch (Exception e) {
                System.out.println("SERVIDOR SECUNDARIO CAIU!");
				continue;
			}
			if(passou)
				id++;
		}
	}

	public static void listenServidor() 
    {
		while (true) 
        {
			Socket cliente;
			try 
            {
				cliente = servidor.accept();

				ObjectInputStream in = new ObjectInputStream(cliente.getInputStream());
                
                //RECEBE AS ATUALIZACOES DO SERVIDOR E REALIZA DE ACORDO COM TIPO
				try 
                {
					Mensagem msg = (Mensagem) in.readObject();
					System.out.println("Tipo: " + msg.getTipo() + " tipo do Return" + Globals.NOVOCLIENTE);
                    
                    //SE EH UM NOVO CLIENTE CARREGA TODOS OS PONTOS JA EXIBIDOS E PRINTA NA TELA
					if (msg.getTipo() == Globals.NOVOCLIENTE) 
                    {
						System.out.println("CARREGANDO DADOS...");
						System.out.println("" + msg.getPontos().size());
						listaPontos = new LinkedList<>();
						for(Ponto p : msg.getPontos())
                        {
							listaPontos.add(p);
							//System.out.println("x: "+p.getX()+" y: "+p.getY());
						}
						tela.setPontos(listaPontos);
						tela.repaint();
						Thread.sleep(Globals.atraso);
					}
                    
                    //CASO CONTRARIO EXECUTA AS ATUALIZACOES
                    else if (msg.getTipo() == Globals.ENVIAMUDANCA) 
                    {
						for (Atualizacao atualizacao : msg.getListaAtualizacoes()) 
                        {
							int x, y, cor, indice, dimensionDots;
							switch (atualizacao.getTipo()) 
                            {
                                case Globals.NOVO:
                                    x = atualizacao.getX();
                                    y = atualizacao.getY();
                                    cor = atualizacao.getCor();
                                    dimensionDots = atualizacao.getDimensaoPonto();
                                    Ponto p = new Ponto(x, y, cor, dimensionDots);
                                    listaPontos.add(p);
                                    break;
                                    
                                case Globals.REMOVE:
                                    indice = atualizacao.getIndice();
                                    if (indice >= 0 && listaPontos.size() > 0) {
                                        listaPontos.remove(indice);
                                    }
                                    break;
                                    
                                case Globals.ATUALIZA:
                                    indice = atualizacao.getIndice();
                                    if (indice >= 0 && listaPontos.size() > 0) 
                                    {
                                        x = atualizacao.getX();
                                        y = atualizacao.getY();
                                        cor = atualizacao.getCor();
                                        dimensionDots = atualizacao.getDimensaoPonto();
                                        listaPontos.get(indice).setX(x);
                                        listaPontos.get(indice).setY(y);
                                        listaPontos.get(indice).setCor(cor);
                                        listaPontos.get(indice).setDimensaoPonto(dimensionDots);
                                    }
                                    break;
                                    
                                default:
                                    System.exit(-1);
                                    break;
							}
						}
					}

				} 
                catch (Exception e) {
					// e.printStackTrace();
				}
				cliente.close();
			}
            catch (IOException e) 
            {
				// e.printStackTrace();
			}
		}
	}
    
    //UTILIZADA PARA CONTROLAR A FREQUENCIA DE PONTOS NA TELA
	public static boolean pintar(List<Ponto> a, List<Ponto> b) 
    {
		if (a.size() != b.size())
			return false;
		else
			return true;
	}
    
    //PRINTA OS PONTOS NA TELA
	public static void repintar() 
    {
		while (true) 
        {
			if (!pintar(tela.getPontos(), listaPontos))
				continue;
			tela.setPontos(listaPontos);
			tela.repaint();
			try 
            {
				Thread.sleep(2*Globals.atraso);
			} 
            catch (InterruptedException e) 
            {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}
