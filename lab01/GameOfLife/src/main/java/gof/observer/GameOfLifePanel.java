
package gof.observer;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JPanel;

/*
 *
 * This class represents both the Life game and the UI of that game.
 */
public class GameOfLifePanel extends JPanel {
    protected int cellHeight;
    protected int cellWidth;
    protected int panelWidth;
    protected int panelHeight;
    protected GameOfLife game;

    public GameOfLifePanel(GameOfLife game, int panelWidth, int panelHeight) {
        this.game = game;
        this.panelWidth = panelWidth;
        this.panelHeight = panelHeight;
        this.cellWidth = panelWidth / game.COLS;
        this.cellHeight = panelHeight / game.ROWS;
        initialize();
    }

    protected void initialize() {
        // Set the size of the Panel to  the Width x Height
        this.setSize(game.COLS * cellWidth, game.ROWS * cellHeight);
        this.setPreferredSize(this.getSize());
        this.setBackground(Color.black);
        // Add a listener to the mouse that will cause the life at the x,y
        //  position of the grid to be turned on/off.
        this.addMouseListener(new MouseListener() {
            public void mouseClicked(MouseEvent e) {
            }

            public void mouseEntered(MouseEvent e) {
            }

            public void mouseExited(MouseEvent e) {
            }

            public void mousePressed(MouseEvent e) {
                game.toggle(e.getPoint().y / cellHeight, e.getPoint().x / cellWidth);
            }

            public void mouseReleased(MouseEvent e) {
            }
        });
    }

    // Necessary painting method which draws the lines of the grid and the live cells.
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        drawGrid(g);
        drawLives(g);
    }


    // Draws the lines of the grid.
    protected void drawGrid(Graphics g) {
        int cellSize = this.getHeight() / game.ROWS;
        g.setColor(Color.red);
        for (int i = 1; i < game.COLS; i++) {
            g.drawLine(0, i * cellSize, this.getWidth(), i * cellSize);
        }
        cellSize = this.getWidth() / game.COLS;
        for (int i = 1; i < game.COLS; i++) {
            g.drawLine(i * cellSize, 0, i * cellSize, this.getHeight());
        }
    }

    // Draws all live cells.
    protected void drawLives(Graphics g) {
        g.setColor(Color.red);
        for (int i = 0; i < game.ROWS; i++) {
            for (int j = 0; j < game.COLS; j++) {
                if (game.isAlive(i, j)) {
                    g.fillRect(j * cellWidth, i * cellHeight, cellWidth, cellHeight);
                }
            }
        }
    }


}
