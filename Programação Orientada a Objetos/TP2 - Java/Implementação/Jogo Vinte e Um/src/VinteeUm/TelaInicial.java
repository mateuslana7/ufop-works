package VinteeUm;

import javax.swing.JComboBox;
import javax.swing.JOptionPane;

public class TelaInicial extends javax.swing.JFrame {

    private String opcao;
    
    public TelaInicial() {
        super("Vinte e Um");
        initComponents();
    }
    
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        grupoBotoes = new javax.swing.ButtonGroup();
        enunciado = new javax.swing.JLabel();
        botaoNivelDificil = new javax.swing.JRadioButton();
        botaoNivelFacil = new javax.swing.JRadioButton();
        botaoSair = new javax.swing.JButton();
        botaoJogar = new javax.swing.JButton();
        fundo = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setBackground(new java.awt.Color(255, 255, 255));
        setFocusCycleRoot(false);
        getContentPane().setLayout(new org.netbeans.lib.awtextra.AbsoluteLayout());

        enunciado.setFont(new java.awt.Font("Tahoma", 1, 18)); // NOI18N
        enunciado.setForeground(new java.awt.Color(255, 255, 255));
        enunciado.setText("Escolha um nivel de dificuldade:");
        getContentPane().add(enunciado, new org.netbeans.lib.awtextra.AbsoluteConstraints(470, 40, -1, -1));

        botaoNivelDificil.setBackground(new java.awt.Color(5, 32, 17));
        grupoBotoes.add(botaoNivelDificil);
        botaoNivelDificil.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        botaoNivelDificil.setForeground(new java.awt.Color(255, 255, 255));
        botaoNivelDificil.setText("Avançado");
        getContentPane().add(botaoNivelDificil, new org.netbeans.lib.awtextra.AbsoluteConstraints(670, 140, -1, -1));

        botaoNivelFacil.setBackground(new java.awt.Color(5, 32, 17));
        grupoBotoes.add(botaoNivelFacil);
        botaoNivelFacil.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        botaoNivelFacil.setForeground(new java.awt.Color(255, 255, 255));
        botaoNivelFacil.setText("Iniciante");
        botaoNivelFacil.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                botaoNivelFacilActionPerformed(evt);
            }
        });
        getContentPane().add(botaoNivelFacil, new org.netbeans.lib.awtextra.AbsoluteConstraints(470, 140, -1, -1));

        botaoSair.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        botaoSair.setText("Sair");
        botaoSair.setPreferredSize(new java.awt.Dimension(100, 35));
        botaoSair.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                botaoSairActionPerformed(evt);
            }
        });
        getContentPane().add(botaoSair, new org.netbeans.lib.awtextra.AbsoluteConstraints(1070, 640, 100, -1));

        botaoJogar.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        botaoJogar.setText("Jogar");
        botaoJogar.setPreferredSize(new java.awt.Dimension(100, 35));
        botaoJogar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                botaoJogarActionPerformed(evt);
            }
        });
        getContentPane().add(botaoJogar, new org.netbeans.lib.awtextra.AbsoluteConstraints(1070, 590, -1, -1));

        fundo.setIcon(new javax.swing.ImageIcon(getClass().getResource("/resources/outrasImagens/blackjack.jpg"))); // NOI18N
        getContentPane().add(fundo, new org.netbeans.lib.awtextra.AbsoluteConstraints(0, 0, -1, -1));

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void botaoJogarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_botaoJogarActionPerformed
        // TODO add your handling code here:
        int op = 1, cont=1;
        TelaDeJogo telaJogo;
        
        //Converte a opcao do numero de rodadas para inteiro
        try 
        {
            op = Integer.parseInt(opcao);
        }
        catch(NumberFormatException e)
        {
            
        }
        
        //Comeca o jogo de acordo com o nivel de dificuldade selecionado
        if(botaoNivelFacil.isSelected())
        {   
            dispose();
            telaJogo = new TelaDeJogo(0);
            telaJogo.criarJogo();
        }
        else if(botaoNivelDificil.isSelected())
        {
            dispose();
            telaJogo = new TelaDeJogo(1);
            telaJogo.criarJogo();
        }
        else
        {
            JOptionPane.showMessageDialog(null, "Selecione um nivel de dificuldade para começar!", "Atenção", JOptionPane.INFORMATION_MESSAGE);
        }
    }//GEN-LAST:event_botaoJogarActionPerformed

    private void botaoNivelFacilActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_botaoNivelFacilActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_botaoNivelFacilActionPerformed

    private void botaoSairActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_botaoSairActionPerformed
        // TODO add your handling code here:
        this.dispose();
    }//GEN-LAST:event_botaoSairActionPerformed

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton botaoJogar;
    private javax.swing.JRadioButton botaoNivelDificil;
    private javax.swing.JRadioButton botaoNivelFacil;
    private javax.swing.JButton botaoSair;
    private javax.swing.JLabel enunciado;
    private javax.swing.JLabel fundo;
    private javax.swing.ButtonGroup grupoBotoes;
    // End of variables declaration//GEN-END:variables
}
