
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JFrame;

public class Frame extends JFrame {
	private static final long serialVersionUID = 1L;
	private List<Ponto> pontos;

	public Frame() {
		pontos = new LinkedList<>();
		this.setPreferredSize(new Dimension(Globals.dimensaoX, Globals.dimensaoY));
		this.pack();
		this.setBackground(Color.BLACK);
		this.setVisible(true);
		this.setResizable(false);
		this.setLocationRelativeTo(null);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
	}

	public void setPontos(List<Ponto> pontos){
		this.pontos = pontos;
	}
	public List<Ponto> getPontos(){
		return this.pontos;
	}
    
	@Override
	public void paint(Graphics g) 
    {
		super.paint(g);
		if (pontos != null)
        {
			for (int i = 0; i < pontos.size(); i++) 
            {
				int coordX = pontos.get(i).getX();
				int coordY = pontos.get(i).getY();
				int dimensaoPonto = pontos.get(i).getDimensaoPonto();
				switch (pontos.get(i).getCor()) 
                {
                    case 0:
                        g.setColor(Color.BLACK);
                        break;
                    case 1:
                        g.setColor(Color.RED);
                        break;
                    case 2:
                        g.setColor(Color.GREEN);
                        break;
                    case 3:
                        g.setColor(Color.BLUE);
                        break;
                    case 4:
                        g.setColor(Color.YELLOW);
                        break;
				}
//				System.out.println("aqui"+coordX+":"+coordY);
//				g.drawLine(coordX, coordY, coordX+1, coordY+1);
				g.fillOval(coordX, coordY, dimensaoPonto, dimensaoPonto);
			}
        }
	}
}
