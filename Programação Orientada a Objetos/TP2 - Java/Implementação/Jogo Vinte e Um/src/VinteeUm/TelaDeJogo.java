package VinteeUm;

import java.applet.Applet;
import java.applet.AudioClip;
import javax.swing.JButton;
import javax.swing.JFrame;
import java.awt.Color;
import java.util.Random;
import java.awt.event.ActionEvent;
import java.awt.event.WindowEvent;
import java.net.URL;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.AbstractAction;
import javax.swing.ActionMap;
import javax.swing.JLabel;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.InputMap;
import javax.swing.JOptionPane;
import javax.swing.KeyStroke;

public class TelaDeJogo extends JFrame 
{
    private static final int COMPRIMENTO = 72;
    private static final int ALTURA = 96;
    private final int nivelJogo;
    private int tamBaralho;
    private final JLabel mesa;
    private final JLabel enunciado;
    private final JLabel enunciadoSoma;
    private final JButton monteDeCartas;
    private final Carta[] maoDoJogador;
    private final TelaInicial tela;
    private final ArrayList<Carta> baralho;
    
    public TelaDeJogo(int tipoJogo) 
    {
        super("BlackJack");
        int i;
        
        //Instancia e/ou inicializa todos os atributos da classe
        mesa = new JLabel();
        baralho = new ArrayList<>();
        tamBaralho = 52;
        maoDoJogador = new Carta[7];
        for(i=0; i<7; i++)
        {
            maoDoJogador[i] = new Carta();
            maoDoJogador[i] = null;
        }
        monteDeCartas = new JButton();
        monteDeCartas.addActionListener(this::monteDeCartasActionPerformed);
        enunciado = new JLabel();
        enunciadoSoma = new JLabel();
        nivelJogo = tipoJogo;
        tela = new TelaInicial();
        
        //Utilizado para jogar atraves do teclado
        InputMap entrada = mesa.getInputMap(JLabel.WHEN_IN_FOCUSED_WINDOW);
        entrada.put(KeyStroke.getKeyStroke("P"), "pedirCarta");
        ActionMap acao = mesa.getActionMap();
        acao.put("pedirCarta", new AbstractAction() 
        {
            @Override
            public void actionPerformed(ActionEvent e) 
            {
                if (monteDeCartas.isEnabled())
                {
                    monteDeCartasActionPerformed(null);
                }
            }
        });
    }
    
    public void criarJogo()
    {
        int i, j, cont=0, x=5, y=5;
        
        //Coloca a imagem do fundo do baralho no monte de cartas
        monteDeCartas.setIcon(new javax.swing.ImageIcon(getClass().getResource("/resources/cartas/fundoa.png")));
        
        //Faz as configurações adequadas dos enunciados
        enunciado.setFont(new java.awt.Font("Tahoma", 1, 32));
        enunciado.setForeground(Color.white);
        enunciado.setText("Para solicitar uma carta clique no baralho ou aperte 'P'");
        enunciado.setBounds(5, 5, 1000, 60);
        enunciado.setVisible(true);
        
        enunciadoSoma.setFont(new java.awt.Font("Tahoma", 1, 36));
        enunciadoSoma.setForeground(Color.white);
        enunciadoSoma.setBounds(30, 550, 200, 60);
        enunciadoSoma.setVisible(true);
        
        //Cria o baralho e cria a mesa
        criarBaralho();
        mesa.setIcon(new javax.swing.ImageIcon(getClass().getResource("/resources/outrasImagens/redTexture.jpg")));
        this.add(mesa);
        mesa.setLayout(null);
        
        //Cria a janela 
        this.setSize(900,650);
        this.setVisible(true);
        this.setLocationRelativeTo(null);
        this.setResizable(false);
        playSound("cardPlace");
        try {
            Thread.sleep(500);
        } catch (InterruptedException ex) {
            Logger.getLogger(TelaDeJogo.class.getName()).log(Level.SEVERE, null, ex);
        }
        playSound("cardPlace");
        
        //Chama a função que colocar duas cartas iniciais na mao do jogador e exibe a soma das duas na tela
        criarMaoDoJogador();
        enunciadoSoma.setText("Soma: "+(maoDoJogador[0].getValor() + maoDoJogador[1].getValor()));
        
        //Exibe a mao do jogador na tela
        maoDoJogador[0].setBounds(350, 405, COMPRIMENTO, ALTURA);
        maoDoJogador[1].setBounds(445, 405, COMPRIMENTO,ALTURA);
        this.mesa.add(maoDoJogador[0]);
        this.mesa.add(maoDoJogador[1]);
        
        //Exibe o monte de cartas na tela
        monteDeCartas.setBounds(395, 105, COMPRIMENTO, ALTURA);
        this.mesa.add(monteDeCartas);
        this.mesa.add(enunciado);
        this.mesa.add(enunciadoSoma);
        
        //Controla e questiona se o jogador deseja realmente sair quando clica no X
        this.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        this.addWindowListener(new java.awt.event.WindowAdapter() 
        {
            @Override
            public void windowClosing(java.awt.event.WindowEvent e) 
            {
                if (e.getID() == WindowEvent.WINDOW_CLOSING)
                {
                    int op = JOptionPane.showConfirmDialog(null,"Deseja realmente sair?", "Atenção", JOptionPane.YES_NO_OPTION);
                    if(op == JOptionPane.YES_OPTION)
                    {
			System.exit(0);  	                	
                    }
                }	
            }
        });
    }
    
    public void criarBaralho()
    {
        int i,j, cont=0;
        Carta[] cartas;
        cartas = new Carta[52];
        for(i=0; i<52; i++)
        {
            cartas[i] = new Carta();
        }
        
        //Colocando no baralho cada uma das cartas dos Áses até o 10's
        for(i=0; i<10; i++)
        {
            for(j=0; j<4; j++)
            {
                switch(j)
                {
                    case 0:
                        cartas[cont].setImagem((i+1)+"c.png");
                        cartas[cont].setValor(i+1);
                        break;
                    case 1:
                        cartas[cont].setImagem((i+1)+"e.png");
                        cartas[cont].setValor(i+1);
                        break;
                    case 2:
                        cartas[cont].setImagem((i+1)+"o.png");
                        cartas[cont].setValor(i+1);
                        break;
                    case 3:
                        cartas[cont].setImagem((i+1)+"p.png");
                        cartas[cont].setValor(i+1);
                        break;
                }
                cont++;
            }
        }
        
        char nome = 'j';
        
        //Colocando no baralho os reis(K), valetes(J) e damas(Q)
        for(i=0; i<3; i++)
        {
            for(j=0; j<4; j++)
            {
                switch(i)
                {
                    case 0:
                        nome = 'j';
                        break;
                    case 1:
                        nome = 'q';
                        break;
                    case 2:
                        nome = 'k';
                        break;
                }
                switch(j)
                {
                    case 0:
                        cartas[cont].setImagem(nome+"c.png");
                        cartas[cont].setValor(10);
                        break;
                    case 1:
                        cartas[cont].setImagem(nome+"e.png");
                        cartas[cont].setValor(10);
                        break;
                    case 2:
                        cartas[cont].setImagem(nome+"o.png");
                        cartas[cont].setValor(10);
                        break;
                    case 3:
                        cartas[cont].setImagem(nome+"p.png");
                        cartas[cont].setValor(10);
                        break;
                }
                cont++;
            }
        }
        
        for(i=0; i<52; i++)
        {
            baralho.add(cartas[i]);
        }
    }
    
    public void criarMaoDoJogador()
    {           
        Random gerador = new Random();
        int carta1;
        
        //Pega duas cartas aleatorias do baralho e coloca na mao do jogador
        carta1 = gerador.nextInt(tamBaralho);
        maoDoJogador[0] = baralho.get(carta1);//coloca a primeira carta
        baralho.remove(carta1);
        tamBaralho--;
        carta1 = gerador.nextInt(tamBaralho);
        maoDoJogador[1] = baralho.get(carta1);//coloca a segunda carta
        baralho.remove(carta1);
        tamBaralho--;
    }
    
    private void monteDeCartasActionPerformed(ActionEvent evt) 
    {
        int i, cont=0, soma=0, carta=0;
        Random gerador = new Random();
        
        //Percorre a mao e verifica se o jogador atingiu o numero maximo de cartas que pode ter em mãos
        for(i=0; i<7; i++)
        {
            if(maoDoJogador[i] != null)
            { 
                cont++;
                soma += maoDoJogador[i].getValor();
            }
        }
        
        //Se atingiu o numero maximo encerra o jogo
        /*if(cont==7)
        {
            System.out.println("Entrou!");
            redesenhaMesa(350,405);
            monteDeCartas.setEnabled(false);
            if(soma == 21)
            {
                JOptionPane.showMessageDialog(null, "Limite de cartas na mao atingido!",null,JOptionPane.INFORMATION_MESSAGE);
                criarTelaVitoria();
                dispose();
            }
            else
            {
                JOptionPane.showMessageDialog(null, "Limite de cartas na mao atingido!","Fim de jogo",JOptionPane.INFORMATION_MESSAGE);
                criarTelaDerrota();
                dispose();
            }
        }*/
        
        //Pega uma carta aleatoria do baralho respeitando o nivel de dificuldade
        if(nivelJogo == 0)
        {
            carta = gerador.nextInt(4);
        }
        else if(nivelJogo == 1)
        {
            carta = gerador.nextInt(tamBaralho);
        }
        
        //Adiciona a carta a mao do jogador caso ele não tenha alcançado o numero maximo de cartas
        System.out.println(cont);
        if(cont < 7)
        {
            playSound("cardPlace");
            adicionarCartaAMao(carta);
        }
         
    }
    
    public void adicionarCartaAMao(int carta)
    {
        int i, cont=0, soma=0;
        
        //Verifica quantas cartas tem na mao do jogador e adiciona uma carta a mao do jogador
        for(i=0; i<7; i++)
        {
            if(maoDoJogador[i] != null)
            {
                cont++;
            }
        }
        maoDoJogador[cont] = baralho.get(carta);//adiciona na proxima posicao vazia do vetor da mao do jogador
        baralho.remove(carta);
        tamBaralho--;
        
        //Soma a quantidade de pontos do jogador e exibe na tela
        for(i=0; i<cont+1; i++)
        {
            soma += maoDoJogador[i].getValor();
        }
        enunciadoSoma.setText("Soma: "+soma);
        
        redesenhaMesa(350,405);//Desenha a mesa novamente adicionando uma carta a tela
        //Clausulas condicionais para verificar se o jogador ganhou ou estourou
        if(cont<6)
        {
            if(soma == 21)
            {
                criarTelaVitoria();
                dispose();
            }

            else if(soma > 21)
            {
                criarTelaDerrota();
                dispose();
            }
        }
    }
    
    public void centralizaCartasDaMao(int x, int x1, int y, int cont)
    {
        //Calcula e reorganiza as cartas do jogador para ficarem centralizadas
        x-=x1;
        for(int i=0; i<cont; i++)
        {
            maoDoJogador[i].setBounds(x,y,COMPRIMENTO,ALTURA);
            this.mesa.add(maoDoJogador[i]);
            x+=95;
        }
    }
    
    public void redesenhaMesa(int x, int y)
    {
        
        int i, cont=2, x1 = 235, soma=0;
        
        //Exibe o monte de cartas
        monteDeCartas.setBounds(395, 105, COMPRIMENTO, ALTURA);
        this.mesa.add(monteDeCartas);
        
        //Verifica o numero de cartas do jogador
        for(i=2; i<7; i++)
        {
            if(maoDoJogador[i] != null)
            {
                cont++;
            }
        }
        
        //Desenha novamente as catas da mao do jogador na mesa centralizando-as
        switch(cont)
        {
            case 3:
            {
                x-=100;
                for(i=0; i<cont; i++)
                {
                    maoDoJogador[i].setBounds(x,y,COMPRIMENTO,ALTURA);
                    this.mesa.add(maoDoJogador[i]);
                    x+=95;
                }
                centralizaCartasDaMao(x,x1,y,cont);
                break;
            }
            
            case 4:
            {
                x-=200;
                for(i=0; i<cont; i++)
                {
                    maoDoJogador[i].setBounds(x,y,COMPRIMENTO,ALTURA);
                    this.mesa.add(maoDoJogador[i]);
                    x+=95;
                }
                centralizaCartasDaMao(x,x1+50,y,cont);
                break;
            }
            case 5:
            {
                x-=300;
                for(i=0; i<cont; i++)
                {
                    maoDoJogador[i].setBounds(x,y,COMPRIMENTO,ALTURA);
                    this.mesa.add(maoDoJogador[i]);
                    x+=95;
                }
                centralizaCartasDaMao(x,x1+80,y,cont);
                break;
            }
            case 6:
            {
                x-=400;
                for(i=0; i<cont; i++)
                {
                    maoDoJogador[i].setBounds(x,y,COMPRIMENTO,ALTURA);
                    this.mesa.add(maoDoJogador[i]);
                    x+=95;
                }
                centralizaCartasDaMao(x,x1+120,y,cont);
                break;
            }
            case 7:
            {
                x-=500;
                for(i=0; i<cont; i++)
                {
                    maoDoJogador[i].setBounds(x,y,COMPRIMENTO,ALTURA);
                    this.mesa.add(maoDoJogador[i]);
                    x+=95;
                }
                centralizaCartasDaMao(x,x1+170,y,cont);
                monteDeCartas.setEnabled(false);
                
                for(i=0; i<7; i++)
                {
                    soma += maoDoJogador[i].getValor();
                }
                if(soma == 21)
                {
                    JOptionPane.showMessageDialog(null, "Limite de cartas na mao atingido!","Fim de jogo",JOptionPane.INFORMATION_MESSAGE);
                    criarTelaVitoria();
                    dispose();
                }
                else
                {
                    JOptionPane.showMessageDialog(null, "Limite de cartas na mao atingido!","Fim de jogo",JOptionPane.INFORMATION_MESSAGE);
                    criarTelaDerrota();
                    dispose();
                }
                break;
            }
        }
    }
    
    //Cria e instancia a tela e os componentes que vão exibir a mensagem de derrota
    public void criarTelaDerrota()
    {
        int opcao;
        
        //Pega uma imagem e guarda na variavel figura
        Icon figura = new ImageIcon (getToolkit().createImage(getClass().getResource("/resources/outrasImagens/imgDerrota.png")));
        
        //Toca o som de derrota e exibe uma tela de fim de jogo
        playSound("youLoseSound");
        JOptionPane.showMessageDialog(null,null,"Fim de jogo",JOptionPane.PLAIN_MESSAGE,figura);
        monteDeCartas.setEnabled(false);
        
        //Oferece a opcao de começar ou não um novo jogo ao usuario
        opcao = JOptionPane.showConfirmDialog(null, "Deseja jogar novamente ?", "Mensagem", JOptionPane.YES_NO_OPTION);
        if(opcao == JOptionPane.YES_OPTION)
        {
            tela.setVisible(true);
            tela.setLocationRelativeTo(null);
            tela.setResizable(false);
            baralho.clear();
        }
        else
        {
            System.exit(0);
        }
    }
    
    public void criarTelaVitoria()
    {
        int opcao;
        
        //Pega uma imagem e guarda na variavel figura
        Icon figura = new ImageIcon (getToolkit().createImage(getClass().getResource("/resources/outrasImagens/imagemVitoria.png"))); 
        
        //Toca o som de vitoria e exibe uma tela de fim de jogo
        playSound("youWinSound");
        JOptionPane.showMessageDialog(null, null,"Fim de jogo",JOptionPane.PLAIN_MESSAGE,figura);
        monteDeCartas.setEnabled(false);
        
        //Oferece a opcao de começar ou não um novo jogo ao usuario
        opcao = JOptionPane.showConfirmDialog(null, "Deseja jogar novamente ?", "Mensagem", JOptionPane.YES_NO_OPTION);
        if(opcao == JOptionPane.YES_OPTION)
        {
            tela.setVisible(true);
            tela.setLocationRelativeTo(null);
            tela.setResizable(false);
            baralho.clear();
        }
        else
        {
            System.exit(0);
        }
    }
    
    public void playSound (String soundName)
    {
        //Pega o som no diretorio e toca
        URL url = getClass().getResource(soundName+".wav");
        AudioClip audio = Applet.newAudioClip(url);
        audio.play();
    }
}