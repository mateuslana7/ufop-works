package nomoredodoiweb;

import java.util.List;
import java.util.ArrayList;

public class VendasRealizadas {

    private static List<Venda> vendas = new ArrayList<Venda>();

    VendasRealizadas(){}

    public static void adicionaVenda(Venda venda){
        vendas.add(venda);
    }

    public static Integer totalVendasRealizadas(){
        return vendas.size();
    }

    public static Integer quantidadeItensVendidos(){
        Integer cont = 0;
        for (Venda venda : vendas){
            cont += venda.getQuantidadeItens();
        }
        return cont;
    }

    public static Double lucroObtido(){
        Double cont = 0.0;
        for (Venda venda : vendas){
            cont += venda.getValorTotal();
        }
        return cont;
    }
}
