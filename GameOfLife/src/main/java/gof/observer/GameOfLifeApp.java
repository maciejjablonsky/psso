
package gof.observer;


import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JButton;

/*
 *
 * This is the main class of the application.
 */
public class GameOfLifeApp extends JFrame {
    protected GameOfLifePanel game;
    protected JPanel contentPane;
    protected JButton advanceButton;
    protected final static int WIDTH_PAD = 50;
    protected final static int HEIGHT_PAD = 100;

    // Build the appropriate instance of the GameOfLifePanel class and initialize the
    //  application frame.
    public GameOfLifeApp(String title, int rows, int cols, int lifeExpectancy, int width, int height) {
        super(title);
        game = new GameOfLifePanel(rows, cols, lifeExpectancy, width, height);
        advanceButton = new JButton("Advance");
        contentPane = new JPanel();
        initialize();
    }

    // Build the UI and set the "advance" button to cause the game object to 
    //  advance one generation.
    protected void initialize() {
        this.setSize(game.getWidth() + WIDTH_PAD, game.getHeight() + HEIGHT_PAD);
        contentPane.setLayout(new FlowLayout());
        contentPane.add(game);
        contentPane.add(advanceButton);
        this.setContentPane(contentPane);
        this.setVisible(true);
        advanceButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                game.advance();
            }
        });
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
    }
}
