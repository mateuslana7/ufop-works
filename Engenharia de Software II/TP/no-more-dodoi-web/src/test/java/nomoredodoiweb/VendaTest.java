package nomoredodoiweb;

import java.util.Arrays;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class VendaTest {

    @Test
    public void testSemDesconto() {
        Medicamento medicamento = new Medicamento(0, 49, 1.00, "Beractanto");
        Venda venda = new Venda(Arrays.asList(medicamento));
        assertEquals((Double) 49.00, venda.getValorTotal()); // não deve haver qualquer desconto
    }

    @Test
    public void testCincoPorcentoDesconto() {
        Medicamento medicamento = new Medicamento(0, 51, 1.00, "Beractanto");
        Venda venda = new Venda(Arrays.asList(medicamento));
        assertEquals((Double) 48.45, venda.getValorTotal()); // desconto de cinco porcento
    }

    @Test
    public void testDezPorcentoDesconto() {
        Medicamento medicamento = new Medicamento(0, 101, 1.00, "Beractanto");
        Venda venda = new Venda(Arrays.asList(medicamento));
        assertEquals((Double) 90.9, venda.getValorTotal()); // desconto de dez porcento
    }

    @Test
    public void testDezPorcentoDescontoLimite() {
        Medicamento medicamento = new Medicamento(0, 100, 1.00, "Beractanto");
        Venda venda = new Venda(Arrays.asList(medicamento));
        assertEquals((Double) 90.0, venda.getValorTotal());
    }

    @Test
    public void testeQuantidadeProdutos() {
        Venda venda = new Venda(Arrays.asList(
                new Medicamento(0, 1, 1.00, "Acarbose"),
                new Medicamento(0, 1, 1.00, "ELOCON"),
                new Medicamento(0, 1, 1.00, "SOTRET")));
        assertEquals((Integer) 3, venda.getQuantidadeItens());
    }
}
