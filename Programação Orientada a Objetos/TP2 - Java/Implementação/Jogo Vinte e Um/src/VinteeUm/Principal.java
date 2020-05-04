package VinteeUm;
/**
 * Aluno: Mateus Vitor Pereira Lana
 * Matricula: 15.1.4340
*/
public class Principal {
    
    public static void main(String args[]) 
    {
        //Cria a tela inicial
        java.awt.EventQueue.invokeLater(() -> {
            TelaInicial tela = new TelaInicial();
            tela.setVisible(true);
            tela.setLocationRelativeTo(null);
            tela.setResizable(false);
        });
    }
    
}