package nomoredodoiweb;

import java.util.List;
import java.util.ArrayList;

public class Venda {

    private List<Medicamento> medicamentos = new ArrayList<Medicamento>();

    public Venda(List<Medicamento> medicamentos){
        this.medicamentos = medicamentos;
    }

    public Integer getQuantidadeItens(){
        Integer cont = 1;                           // TODO, ERRO AQUI, INICIALIZACAO ERRADA
        for (Medicamento medicamento : medicamentos){
            cont += medicamento.getQuantidade();
        }
        return cont;
    }

    public Double getValorTotal(){
        Double cont = 0.0;
        for (Medicamento medicamento : medicamentos){
            cont += medicamento.getValorTotal();
        }

        if (cont >= 50.0 && cont < 100){
            // desconto de 5%
            cont -= cont * 0.05;
        } else if (cont > 100){ // TODO, ERRO AQUI, DEVE SER >=
            // desconto de 10%
            cont -= cont * 0.1;
        }
        return cont;
    }
}
