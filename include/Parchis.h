#ifndef __PARCHIS_H__
#define __PARCHIS_H__

# include <tuple>
# include "Dice.h"
# include "Board.h"
# include "GUIPlayer.h"
# include "Player.h"
#include <iostream>
#include <algorithm>


using namespace std;

class Parchis{
    private:
        Board board;
        Dice dice;
        vector<tuple <color, int, Box, Box>> last_moves;
        int last_dice;
        
        //0: yellow & red, 1: blue and green.
        int current_player;
        color current_color;
        vector <Player*> players;

        int illegal_move_player;

        static const int final_red_box = 34;
        static const int final_blue_box = 17;
        static const int final_green_box = 51;
        static const int final_yellow_box = 68;

        static const int init_red_box = 38;
        static const int init_blue_box = 21;
        static const int init_green_box = 55;
        static const int init_yellow_box = 4;

        static const vector<int> safe_boxes;

        /**
         * @brief
         *
         */
        void nextTurn();

    public:
        static const vector<color> game_colors;
        
        /**
         * @brief Default construct a new Parchis object
         * 
         */
        Parchis();

        /**
         * @brief Construct a new Parchis object
         * 
         * @param b 
         */
        Parchis(const BoardConfig &b);

        /**
         * @brief Construct a new Parchis object
         * 
         * @param b 
         * @param d 
         */
        Parchis(const Board & b, const Dice & d);

        /**
         * @brief Construct a new Parchis object
         * 
         * @param b 
         * @param d 
         */
        Parchis(const BoardConfig & b, const Dice & d);

        /**
         * @brief Construct a new Parchis object
         * 
         * @param b 
         * @param d 
         * @param p1 
         * @param p2 
         */
        Parchis(const Board & b, const Dice & d, Player & p1, Player & p2);

        /**
         * @brief Construct a new Parchis object
         * 
         * @param b 
         * @param d 
         * @param p1 
         * @param p2 
         */
        Parchis(const BoardConfig &b, const Dice &d, Player &p1, Player &p2);

        /**
         * @brief Get the Dice object
         * 
         * @param player 
         * @return const vector<int>& 
         */
        const Dice & getDice ();


         /**
         * @brief Get the Board object
         * 
         * @param player 
         * @return const vector<int>& 
         */
        const Board & getBoard () const;

        /**
         * @brief Get the Available Pieces object
         * 
         * @param player 
         * @param dice_number 
         * @return const vector<int>& 
         */
        const vector<int> getAvailablePieces (color player, int dice_number);

        /**
         * @brief Mover la pieza número "piece" del jugador "player" "dice_number" posiciones.
         * 
         * @param player 
         * @param piece 
         * @param dice_number 
         */
        void movePiece(color player, int piece, int dice_number);

        /**
         * @brief Comprobar si un movimiento es válido.
         * 
         * @param player 
         * @param box 
         * @param dice_number 
         * @return true 
         * @return false 
         */
        bool isLegalMove(color player, const Box & box, int dice_number);

        /**
         * @brief Get the Last Moves object
         * 
         * @return const vector<tuple <color, int, Box>>& 
         */
        const vector<tuple <color, int, Box, Box>> & getLastMoves();


        /**
         * @brief Get the Last Dice object
         * 
         * @return int 
         */
        int getLastDice();

        /**
         * @brief Obtener la ocupación de un box
         * 
         * @param box 
         * @return vector<pair <color, int>> 
         */
        const vector<pair <color, int>> boxState(const Box & box) const;

        /**
         * @brief Función que devuelve el color del muro (en caso de haberlo) en la casilla "box"
         * 
         * @param b 
         * @return const color 
         */
        const color isWall(const Box & b) const;

        /**
         * @brief Función que devuelve el vector de colores de los muros (en caso de haberlos) del
         * camino entre b1 y b2.
         * 
         * @param b1 
         * @param b2 
         * @return const vector<color> 
         */
        const vector<color> anyWall(const Box & b1, const Box & b2) const;

        /**
         * @brief Función auxiliar que calcula la casilla destino tras aplicar el movimiento.
         * 
         * @param player 
         * @param box 
         * @param dice_number 
         * @return const Box 
         */
        const Box computeMove(color player, const Box & box, int dice_number, bool * goal_bounce = NULL) const;

        


        /**
         * @brief 
         * 
         */
        void gameLoop();


        /**
         * @brief 
         * 
         */
        bool gameStep();

        /**
         * @brief Get the Current Player object
         * 
         * @return int 
         */
        inline int getCurrentPlayer(){
            return current_player;
        }

        /**
         * @brief Get the Current Color object
         * 
         * @return color 
         */
        inline color getCurrentColor(){
            return this->current_color;
        }

        /**
         * @brief Indica si la partida ha terminado.
         * 
         * @return true 
         * @return false 
         */
        bool gameOver();
        
        /**
         * @brief Si la partida ha terminado, devuelve el índice del jugador ganador (0 o 1).
         * 
         * @return int 
         */
        int getWinner();

        /**
         * @brief Si la partida ha terminado, devuelve el color del jugador ganador.
         * 
         * @return color 
         */
        color getColorWinner();

        /**
         * @brief Devuelve true si y solo si uno de los jugadores ha hecho un movimiento ilegal.
         * El jugador que ha hecho dicho movimiento pierde automáticamente.
         * 
         * @return true 
         * @return false 
         */
        bool illegalMove();
};


#endif 