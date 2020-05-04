package VinteeUm;

public enum Medidas {
    
    COMPRIMENTO(72),ALTURA(96),LARGURA_TELA(900),ALTURA_TELA(650);
    
    public int valorMedida;
    
    Medidas(int valor)
    {
        valorMedida = valor;
    }
    
    public int getValorMedida()
    {
        return valorMedida;
    }
    
}
