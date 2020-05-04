import java.io.Serializable;
import java.util.List;

public class Mensagem implements Serializable{
	
	private static final long serialVersionUID = 1L;
	private int tipo;
	private String origem;
	private String destino;
	private List<Ponto> pontos;
	private List<Atualizacao> listaAtualizacoes;
	private Atualizacao atualizacao;
	
	public List<Atualizacao> getListaAtualizacoes() {
		return listaAtualizacoes;
	}

	public void setListaAtualizacoes(List<Atualizacao> filaAlteracoes) {
		this.listaAtualizacoes = filaAlteracoes;
	}

	public Atualizacao getAtualizacao() {
		return atualizacao;
	}

	public void setAtualizacao(Atualizacao atualizacao) {
		this.atualizacao = atualizacao;
	}

	public List<Ponto> getPontos() {
		return pontos;
	}

	public void setPontos(List<Ponto> pontos) {
		this.pontos = pontos;
	}
	
	public Mensagem() {
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
	public String getDestino() {
		return destino;
	}

	public void setDestino(String destino) {
		this.destino = destino;
	}
	
}