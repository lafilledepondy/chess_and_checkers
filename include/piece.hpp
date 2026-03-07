#pragma once

#include "position.hpp"
#include "plateau.hpp"

class Piece {
    private:
        // ----------------------------------------------------------------------------
        // private attribute
        // ----------------------------------------------------------------------------    
        const std::string _name;
        const bool _isBlack;

    public:
        // ----------------------------------------------------------------------------
        // constructors
        // ----------------------------------------------------------------------------    
        Piece(bool isBlack, std::string name) : 
            _name(name), _isBlack(isBlack) {};

        // ----------------------------------------------------------------------------
        // abstract methods
        // ---------------------------------------------------------------------------- 
        virtual bool isValidMove(Position &start_p, Position &end_p, Position &capture_p, Plateau* plateau) = 0;

        // ----------------------------------------------------------------------------
        // methods
        // ----------------------------------------------------------------------------         
        std::string toString() const;
};