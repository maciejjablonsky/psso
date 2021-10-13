package gof.observer;

/*
 * The main program used to invoke the game of life system.
 */

public class Main {

    public static void main(String[] args) {
        GameOfLife game = new GameOfLife(20, 20, 10);
        GameOfLifePanel panel = new GameOfLifePanel(game, 400, 400);
        GameOfLifeUI ui = new GameOfLifeUI("The Game of Life", game, panel);
        game.addObserver(ui);
    }
}

