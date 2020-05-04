

import java.sql.Timestamp;
import java.util.ArrayList;

public class MensagemF implements Message{
	public final static int RESPOSTA = 0;
	public final static int REQUISICAO = 1;
	public final static int WAKEUP = 2;
	public final static int FINALIZA = 3;
	public final static int LOGIN = 4;
	public final static int INICIAR = 5;
	
	
	private int tipo;
	private Timestamp tempoMensagem;//tempo inicial que comecou a msg
	private String id;
	private ArrayList<String> vizinhos;
	
	
	
	public MensagemF(){
		setTimestamp(new Timestamp(System.currentTimeMillis()));
	}
	
	@Override
	public int getTipo() {
		return tipo;
	}

	@Override
	public void setTipo(int tipo) {
		this.tipo = tipo;		
	}

	public ArrayList<String> getVizinhos() {
		return vizinhos;
	}

	public void setVizinhos(ArrayList<String> vizinhos) {
		this.vizinhos = vizinhos;
	}

	public Timestamp getTimestamp() {
		return tempoMensagem;
	}

	public void setTimestamp(Timestamp tempoMensagem) {
		this.tempoMensagem = tempoMensagem;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

}