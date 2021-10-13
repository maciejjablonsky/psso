
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
    public final int ROWS;
    public final int COLS;
    public final int LIFE_EXPECTANCY;
    protected int cellHeight;
    protected int cellWidth;
    protected int panelWidth;
    protected int panelHeight;
    protected int grid[][]; // Holds the dead (0) and alive cells (1, 2, ..., LIFE_EXPECTANCY).

    public GameOfLifePanel(int rows, int cols, int lifeExpectancy, int panelWidth, int panelHeight) {
        this.ROWS = rows;
        this.COLS = cols;
        this.LIFE_EXPECTANCY = lifeExpectancy;
        this.panelWidth = panelWidth;
        this.panelHeight = panelHeight;
        this.cellWidth = panelWidth / cols;
        this.cellHeight = panelHeight / rows;
        grid = new int[rows][cols];
        initialize();
    }

    protected void initialize() {
        // Set the size of the Panel to  the Width x Height
        this.setSize(COLS * cellWidth, ROWS * cellHeight);
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
                toggle(e.getPoint().y / cellHeight, e.getPoint().x / cellWidth);
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

    // Reverse the life status of the cell at location r,c
    public void toggle(int r, int c) {
        if (isAlive(r, c)) grid[r][c] = 0;
        else grid[r][c] = LIFE_EXPECTANCY;
        repaint();
    }

    public boolean isAlive(int r, int c) {
        return (grid[r][c] != 0);
    }

    // Draws the lines of the grid.
    protected void drawGrid(Graphics g) {
        int cellSize = this.getHeight() / ROWS;
        g.setColor(Color.red);
        for (int i = 1; i < COLS; i++) {
            g.drawLine(0, i * cellSize, this.getWidth(), i * cellSize);
        }
        cellSize = this.getWidth() / COLS;
        for (int i = 1; i < COLS; i++) {
            g.drawLine(i * cellSize, 0, i * cellSize, this.getHeight());
        }
    }

    // Draws all live cells.
    protected void drawLives(Graphics g) {
        g.setColor(Color.red);
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (isAlive(i, j)) {
                    g.fillRect(j * cellWidth, i * cellHeight, cellWidth, cellHeight);
                }
            }
        }
    }

    // Returns the number of alive neighbors for the cell at position r,c.  The
    //  grid is finite but unbound, meaning that the neighbor relation wraps around
    //  the grid boundaries.
    protected int nbrOfNeighbors(int r, int c) {
        int n = 0;
        int x = 0;
        int y = r - 1;
        if (y < 0) y = ROWS - 1;
        for (int rCt = 1; rCt <= 3; rCt++) {
            x = c - 1;
            if (x < 0) x = COLS - 1;
            for (int cCt = 1; cCt <= 3; cCt++) {
                if (x != c || y != r) {
                    if (isAlive(y, x)) {
                        n++;
                    }
                }
                x = (x + 1) % COLS;
            }
            y = (y + 1) % ROWS;
        }
        return n;
    }

    // This method implements the rules of the Game of Life.  For each cell,
    //  we simple find the number of neighbors and then bring the cell to life
    //  if appropriate. 
    // a live cell with 2, 3 neighbors stays alive.
    // a non-existent cell comes alive if it has 3 neighbors
    public void advance() {
        int[][] newGrid = new int[ROWS][COLS];
        int n = 0;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                n = nbrOfNeighbors(i, j);
                if (isAlive(i, j)) {
                    if (n == 2 || n == 3) {
                        newGrid[i][j] = grid[i][j] - 1;
                    } else {
                        newGrid[i][j] = 0;
                    }
                } else {
                    if (n == 3) {
                        newGrid[i][j] = LIFE_EXPECTANCY;
                    } else {
                        newGrid[i][j] = 0;
                    }
                }

            }
        }
        grid = newGrid;
        repaint();
    }
}
