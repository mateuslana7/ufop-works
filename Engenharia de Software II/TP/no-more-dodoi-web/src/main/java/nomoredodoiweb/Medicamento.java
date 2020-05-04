package nomoredodoiweb;

public class Medicamento {
    private Integer codigo;
    private Integer quantidade;
    private Double preco; // preco unitario
    private Double precoTotal; // preco de todos os produtos
    private String nome;

    public Medicamento(Integer codigo, Integer quantidade, Double preco, String nome){
        this.codigo = codigo;
        this.quantidade = quantidade;
        this.preco = preco;
        this.precoTotal = preco * quantidade;
        this.nome = nome;
    }

    public void vende(Integer quantidade){
        this.quantidade -= quantidade;
    }

    public Double getValorTotal(){
        return this.precoTotal;
    }

    public Integer getQuantidade(){
        return this.quantidade;
    }

    public boolean equals(Medicamento p){
        return (p.codigo.equals(this.codigo) && p.preco.equals(this.preco));
    }
}
