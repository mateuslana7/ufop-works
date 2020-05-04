package nomoredodoiweb;

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main (String[] args){

        VendasRealizadas historico = new VendasRealizadas();

        Medicamento medicamento1 = new Medicamento(1, 10, 2.5, "Medicamento 1");
        Medicamento medicamento2 = new Medicamento(2, 20, 5.0, "Medicamento 2");
        Medicamento medicamento3 = new Medicamento(3, 30, 7.5, "Medicamento 3");

        List<Medicamento> medicamentos = new ArrayList<Medicamento>();
        medicamentos.add(medicamento1);
        medicamentos.add(medicamento2);
        medicamentos.add(medicamento3);

        Venda venda = new Venda(medicamentos);
        historico.adicionaVenda(venda);

        System.out.println(historico.totalVendasRealizadas());
        System.out.println(historico.lucroObtido());
        System.out.println(historico.quantidadeItensVendidos());
    }
}
