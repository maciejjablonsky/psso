
package gof.observer;


import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Observable;
import java.util.Observer;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JButton;

/*
 *
 * This is the main class of the application.
 */
public class GameOfLifeUI extends JFrame implements Observer {
    protected GameOfLife game;
    protected GameOfLifePanel panel;
    protected JPanel contentPane;
    protected JButton advanceButton;
    protected final static int WIDTH_PAD = 50;
    protected final static int HEIGHT_PAD = 100;

    // Build the appropriate instance of the GameOfLifePanel class and initialize the
    //  application frame.
    public GameOfLifeUI(String title, GameOfLife game, GameOfLifePanel panel) {
        super(title);
        this.game = game;
        this.panel = panel;
        advanceButton = new JButton("Advance");
        contentPane = new JPanel();
        initialize();
    }

    // Build the UI and set the "advance" button to cause the game object to
    //  advance one generation.
    protected void initialize() {
        this.setSize(panel.getWidth() + WIDTH_PAD, panel.getHeight() + HEIGHT_PAD);
        contentPane.setLayout(new FlowLayout());
        contentPane.add(panel);
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

    public void update(Observable obj, Object arg) {
        panel.repaint();
    }
}
