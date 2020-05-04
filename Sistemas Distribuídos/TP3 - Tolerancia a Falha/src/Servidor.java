import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

public class Servidor {
    
	private static List<String> listaClientes;
	private static ServerSocket servidor;
	private static boolean servidorPincipal;
	public static List<Atualizacao> filaAtualizacoes;//IP DO CLIENTE QUE SOLICITA ATUALIZACAO E QUANTIDADE DE PONTOS
	public static List<Ponto> listaPontos;
	public static String meuIP;
	public static boolean desatualizado = false;

	public static void main(String[] args) throws Exception {
		filaAtualizacoes = new LinkedList<Atualizacao>();
		listaPontos = new LinkedList<>();
		listaClientes = new LinkedList<>();
		//GUARDA O SERVDOR DE BACKUP
		Globals.servidorSecundario = "200.239.139.122";
		servidorPincipal = true;
		new Servidor().executa();
	}

	public Servidor() {
		Servidor.listaClientes = new ArrayList<String>();
	}

	public void executa() throws IOException 
    {
		Servidor.servidor = new ServerSocket(Globals.PORTA);
		servidor.getInetAddress();
		meuIP = InetAddress.getLocalHost().toString().replaceAll(".*/", "");
		System.out.println("SERVIDOR PRINCIPAL ABERTO!!");
        
		new Thread() {
			@Override
			public void run() {
				escutaCliente();//FICA AGUARDANDO SOLICITACOES DE PONTOS
			}
		}.start();

		new Thread() {
			@Override
			public void run() {
				alteraPontos();//ENVIA MENSAGENS PARA ATUALIZAR OS PONTOS
			}
		}.start();
        
		new Thread() {
			@Override
			public void run() {
				verficaClientes();//VERIFICA CONEXAO DOS CLIENTES
			}
		}.start();
	}

	public static void verficaClientes() 
    {
		while (true) 
        {
			try 
            {
				Thread.sleep(Globals.atraso/50);
				for (int i = 0; i < listaClientes.size(); i++) 
                {
					try 
                    {
						InetAddress ping = InetAddress.getByName(listaClientes.get(i));
                        
                        //VERIFICA SE O CLIENTE CAIU E SE ESSE SERVIDOR TEM CONEXAO
						if (!ping.isReachable(Globals.atraso/50) && Globals.ping()) 
                        {
							if (!ping.isReachable(Globals.atraso/50)) 
                            {
								System.out.println("O Cliente: " + listaClientes.get(i) + " caiu!!");
								listaClientes.remove(i);
								break;
							}
						}
					} 
                    catch (Exception e) {

					}
				}
			} 
            catch (Exception e) {
			}

		}
	}

	public static void alteraPontos() 
    {
		while (true) 
        {
			try
            {
				if (servidorPincipal) 
                {
					try 
                    {
						Thread.sleep(10 * Globals.atraso);
						System.out.println("MEU PING: "+Globals.ping());
                        
                        //VERIFICA SE ESSE SERVIDOR TEM CONEXAO
						if (!Globals.ping()) 
                        {
							servidorPincipal = false;
							System.out.println("PERDA DE CONEXAO PARA ESSE SERVIDOR...");
							continue;
						}
					}
                    catch (Exception e){
					}
					
					//VERIFICA SE MINHA FILA DE ATUALIZACOES POSSUI ITENS E CASO TENHO ATENDE AS MESMAS
					if (filaAtualizacoes.size() > 0) 
                    {
						System.out.println("ATENDENDO SOLICITACAO DO CLIENTE: " + filaAtualizacoes.get(0).getOrigem());
						Random r = new Random();
						Atualizacao atualizacao = filaAtualizacoes.remove(0);

						System.out.println("REALIZANDO ALTERACAO DE: " + atualizacao.getOrigem());
						List<Atualizacao> alteracoes = new LinkedList<>();
						for (int i = 0; i < atualizacao.getQuantidade(); i++) 
						{
							int aleatorio = Math.abs(r.nextInt(4));
							if (aleatorio == 3)
								aleatorio = 0;
							Atualizacao a;
							int indice, x, y, cor, dimensaoPonto;

							switch (aleatorio) 
                            {
                                case Globals.NOVO:
                                    x = r.nextInt(Globals.dimensaoX);
                                    y = r.nextInt(Globals.dimensaoY);
                                    cor = r.nextInt(Globals.COR);
                                    dimensaoPonto = r.nextInt(Globals.tamMaxPonto);

                                    Ponto p = new Ponto(x, y, cor, dimensaoPonto);
                                    listaPontos.add(p);

                                    a = new Atualizacao();
                                    a.setOrigem(meuIP);
                                    a.setTipo(Globals.NOVO);
                                    a.setX(x);
                                    a.setY(y);
                                    a.setCor(cor);
                                    a.setDimensaoPonto(dimensaoPonto);
                                    a.setId(atualizacao.getId());
                                    
                                    alteracoes.add(a);
                                    break;
                                    
                                case Globals.REMOVE:
                                    if (listaPontos.size() == 0)
                                        continue;
                                    indice = r.nextInt(listaPontos.size());
                                    if (indice >= 0 && listaPontos.size() > 0) 
                                    {
                                        listaPontos.remove(indice);
                                        a = new Atualizacao();
                                        a.setOrigem(meuIP);
                                        a.setTipo(Globals.REMOVE);
                                        a.setIndice(indice);
                                        a.setId(atualizacao.getId());
                                        
                                        alteracoes.add(a);
                                    }
                                    break;
                                    
                                case Globals.ATUALIZA:
                                    if (listaPontos.size() == 0)
                                        continue;
                                    indice = r.nextInt(listaPontos.size());
                                    if (indice >= 0 && listaPontos.size() > 0) 
                                    {
                                        x = r.nextInt(Globals.dimensaoX);
                                        y = r.nextInt(Globals.dimensaoY);
                                        cor = r.nextInt(Globals.COR);
                                        dimensaoPonto = r.nextInt(Globals.tamMaxPonto);

                                        listaPontos.get(indice).setX(x);
                                        listaPontos.get(indice).setY(y);
                                        listaPontos.get(indice).setCor(cor);
                                        listaPontos.get(indice).setDimensaoPonto(dimensaoPonto);

                                        a = new Atualizacao();
                                        a.setOrigem(meuIP);
                                        a.setTipo(Globals.ATUALIZA);
                                        a.setCor(cor);
                                        a.setX(x);
                                        a.setY(y);
                                        a.setDimensaoPonto(dimensaoPonto);
                                        a.setIndice(indice);
                                        a.setId(atualizacao.getId());

                                        alteracoes.add(a);
                                    }

                                    break;
                                default:
                                    //System.out.println("nao era para cair aqui");
                                    System.exit(-1);
                                    break;
							}

						}
						try 
                        {
                            //ENVIA O BACKUP DE ATUALIZACOES AO SERVIDOR SECUNDARIO
							Globals.enviarMensagem(meuIP, Globals.servidorSecundario, Globals.COPIA, Globals.PORTA, listaPontos, filaAtualizacoes);
						}
                        catch (Exception e) {

						}
						for (String cliente : listaClientes) 
                        {
							try 
                            {
                                //ENVIA AS ALTERACOES DOS PONTOS AOS CLIENTES
								Globals.enviarMensagem(meuIP, cliente, Globals.ENVIAMUDANCA, Globals.PORTA, alteracoes);
							} 
                            catch (Exception e) {

							}
						}
						System.out.println("\t" + atualizacao.getQuantidade() + " ATUALIZACOES ENVIADAS PARA OS " + listaClientes.size() + " CLIENTES!");
					}
				}
				
                //CASO CONTRARIO VERIFICA CONEXAO DO OUTRO SERVIDOR
                else 
                {
					try {
						InetAddress ping = InetAddress.getByName(Globals.servidorSecundario);

						if (!ping.isReachable(Globals.atraso/50) && Globals.ping())
                        {
							if (!ping.isReachable(Globals.atraso/50))
                            {
								System.out.println("SERVIDOR: " + Globals.servidorSecundario + " PERDEU CONEXAO, ASSUMINDO SERVIDOR PRINCIPAL...");
								desatualizado = true;
								servidorPincipal = true;
							}
						}
					} 
                    catch (Exception e) {
					}
				}
			} 
            catch (Exception e) 
            {
				e.printStackTrace();
			}
		}
	}

	public static void escutaCliente() 
    {
		while (true) 
        {
			Socket cliente;
			try 
            {

				cliente = servidor.accept();
                //VERIFICA SE TENHO A CONEXAO DE UM NOVO CLIENTE
				if (!listaClientes.contains(cliente.getInetAddress().getHostAddress())) 
                {
					//VERIFICA SE O NOVO CLIENTE NAO EH ALGUM DOS SERVIDORES E FAZ CONEXAO DE NOVO CLIENTE
					if (!cliente.getInetAddress().getHostAddress().equals(Globals.servidorBackup) && !cliente.getInetAddress().getHostAddress().equals(Globals.servidorPrimario)) 
                    {
						System.out.println("NOVA CONEXAO COM O CLIENTE: " + cliente.getInetAddress().getHostAddress()+"!");
						listaClientes.add(cliente.getInetAddress().getHostAddress());
						try 
                        {
							Globals.enviarMensagemNovoCliente(meuIP, cliente.getInetAddress().getHostAddress(), Globals.NOVOCLIENTE, Globals.PORTA, listaPontos);
							System.out.println("ENVIANDO BACKUP DE PONTOS PARA O NOVO CLIENTE CONECTADO...");
						}
                        catch (Exception e) {
							// e.printStackTrace();
						}
					}
				}

				ObjectInputStream in = new ObjectInputStream(cliente.getInputStream());
				
				//VERIFICA A MENSAGEM RECEBIDA DO CLIENTE E ADICIONA NA LISTA DE ALTERACOES
				try
                {
					Mensagem msg = (Mensagem) in.readObject();

					if (msg.getTipo() == Globals.MUDANCA) 
                    {
						filaAtualizacoes.add(msg.getAtualizacao());
					} 
                    else if (msg.getTipo() == Globals.COPIA) 
                    {
						System.out.println("COPIANDO BACKUP DO SERVIDOR PRINCIPAL!");
						filaAtualizacoes = msg.getListaAtualizacoes();
						listaPontos = msg.getPontos();// TODO TALVEZ
					} 
                    else if (msg.getTipo() == Globals.ENVIAMUDANCA) 
                    {
						System.out.println("RECEBENDO ATUALIZACOES!");
						for (Atualizacao atualizacao : msg.getListaAtualizacoes()) 
                        {
							int indice = -1;
							for (int i = 0; i < listaPontos.size(); i++) 
                            {
								if (filaAtualizacoes.get(i).getId().equals(atualizacao.getId())) 
                                {
									indice = i;
									break;
								}
							}
							if (indice >= 0)
								filaAtualizacoes.remove(indice);
                                int x, y, cor, dimensaoPonto;
							switch (atualizacao.getTipo())
                            {
                                case Globals.NOVO:
                                    x = atualizacao.getX();
                                    y = atualizacao.getY();
                                    cor = atualizacao.getCor();
                                    dimensaoPonto = atualizacao.getDimensaoPonto();
                                    Ponto p = new Ponto(x, y, cor, dimensaoPonto);
                                    listaPontos.add(p);
                                    break;
                                case Globals.REMOVE:
                                    indice = atualizacao.getIndice();
                                    if (indice >= 0 && listaPontos.size() > 0)
                                    {
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
                                        dimensaoPonto = atualizacao.getDimensaoPonto();
                                        listaPontos.get(indice).setX(x);
                                        listaPontos.get(indice).setY(y);
                                        listaPontos.get(indice).setCor(cor);
                                        listaPontos.get(indice).setDimensaoPonto(dimensaoPonto);
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
            catch (IOException e) {
				// e.printStackTrace();
			}
		}
	}
}
