

import java.io.Serializable;

public interface Message extends Serializable{
	
	public abstract int getTipo();
	public abstract void setTipo(int tipe);
	
}