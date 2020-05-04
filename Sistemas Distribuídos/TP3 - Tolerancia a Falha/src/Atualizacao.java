import java.io.Serializable;

public class Atualizacao implements  Serializable{
	
	private static final long serialVersionUID = 1L;
	private String id;
	private int tipo;
	private String origem;
	private int quantidade;
	private int indice;
	
	private int x;
	private int y;
	private int cor;
	private int dimensaoPonto;
	
	public int getDimensaoPonto() {
		return dimensaoPonto;
	}
	public void setDimensaoPonto(int dimensaoPonto) {
		this.dimensaoPonto = dimensaoPonto;
	}
	public String getId() {
		return id;
	}
	public void setId(String id) {
		this.id = id;
	}
	public int getX() {
		return x;
	}
	public void setX(int x) {
		this.x = x;
	}
	public int getY() {
		return y;
	}
	public void setY(int y) {
		this.y = y;
	}
	public int getCor() {
		return cor;
	}
	public void setCor(int cor) {
		this.cor = cor;
	}
	public int getIndice() {
		return indice;
	}
	public void setIndice(int indiceRemove) {
		this.indice = indiceRemove;
	}
	public int getTipo() {
		return tipo;
	}
	public void setTipo(int tipo) {
		this.tipo = tipo;
	}
	public String getOrigem() {
		return origem;
	}
	public void setOrigem(String origem) {
		this.origem = origem;
	}
	public int getQuantidade() {
		return quantidade;
	}
	public void setQuantidade(int quantidade) {
		this.quantidade = quantidade;
	}
}
