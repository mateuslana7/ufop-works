package VinteeUm;

import javax.swing.ImageIcon;
import javax.swing.JButton;

public class Carta extends JButton {
    
    private ImageIcon imagem;
    private static final int COMPRIMENTO = 72;
    private static final int ALTURA = 96;
    private int valor;
    private final String caminhoImg = "resources/cartas/";
    
    public Carta()
    {
        imagem = new ImageIcon();
    }
    
    public void setImagem(String nomeArqImg)
    {
        imagem = new javax.swing.ImageIcon(getClass().getResource("/"+caminhoImg+nomeArqImg));
        this.setIcon(imagem);
        this.setPreferredSize(new java.awt.Dimension(COMPRIMENTO, ALTURA));
    }
    
    public void setValor(int valor)
    {
        this.valor = valor;
    }
    
    public int getValor()
    {
        return valor;
    }
}
