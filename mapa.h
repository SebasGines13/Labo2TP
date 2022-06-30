#pragma once
#include <SFML/Graphics.hpp>
#include "IColisionable.h"
#include "Bloque.h"
#include "Item.h"


class Mapa : public sf::Drawable, public sf::Transformable
{
    public:
        /// Constructor
	    Mapa(int sprClase, int nivel, int tilewidth, int tileheight, int mapwidth, int mapheight); 
        /// Destructor
        ~Mapa();
	    /// Gets
        sf::Vector2f         getPlayerSpawn() const;
        sf::Vector2f         getEnemigoSpawn(int i) const;
        int                  getTileWidth() const;
        int                  getTilHeight() const;
        std::vector<Bloque*> getBloques() const;
        Item                 getItem(int tipoItem);
        /// Métodos
        void    spawnItem(sf::Vector2f pos, int tipoItem);
        void    update();
        void    desaparecerItem(int tipoItem);
        bool    getItemVisible(int tipoItem);
        void    cargarMapaDeDisco();
        void	draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del método draw en Drawable.
    private:
        void    generarMapa();
	    sf::Texture*	     _txtMapa; ///textura del mapa
	    int				     _tilewidth; ///Ancho del tile del mapa
	    int				     _tileheight; ///Alto del tile del mapa
	    int				     _sprActual; /// Nro de sprite actual
	    int				     _mapWidth; // Ancho del mapa en tiles
	    int				     _mapHeight; // Alto del mapa en tiles
        int                  _nivel; // nivel actual del mapa
        Item*                _itemPuntos; // Item que puede aparecer
        Item*                _itemVida;
        sf::Vector2f         _spawnPlayer; /// posición donde aparece el personaje.
        sf::Vector2f         _spawnEnemigo[3]; /// posiciones de spawn de enemigos.
	    std::vector<Bloque*> _bloques;/// Vector de bloques 
        std::vector<int>     _vMapa;
};
        
        
  