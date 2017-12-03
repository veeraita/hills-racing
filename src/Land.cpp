#include "Land.hpp"
#include "DEFINITIONS.hpp"

namespace Hills 
{
    Land::Land( GameDataRef data ) : _data(data)
    {
        //sprite that's visible on screen
        sf::Sprite sprite( _data->assets.GetTexture( "Land" ) );
        //sprite that's moving onto screen after the previous sprite 
        //goes off screen
        sf::Sprite sprite2( _data->assets.GetTexture( "Land" ) );
        
        sprite.setPosition( 0, _data->window.getSize( ).y - sprite.getGlobalBounds( ).height / 2 );
        sprite2.setPosition( sprite.getGlobalBounds( ).width, _data->window.getSize( ).y - sprite.getGlobalBounds( ).height / 2 );
        
        _landSprites.push_back( sprite );
        _landSprites.push_back( sprite2 );
    }
    
    void Land::MoveLand( float dt )
    {
            // TODO: move land according to vehicle movement
            
            // switch to next sprite when the previous sprite goes offscreen
        for (unsigned short int i = 0; i < _landSprites.size( ); i++) 
        {
            if ( _landSprites.at( i ).getPosition( ).x < 0 - _landSprites.at( i ).getGlobalBounds( ).width )
            {
                sf::Vector2f position( _data->window.getSize( ).x, _landSprites.at( i ).getPosition( ).y );
                
                _landSprites.at( i ).setPosition( position );
            }
            
        };
    }
    
    void Land::DrawLand( )
    {
        for (unsigned short int i = 0; i < _landSprites.size( ); i++) 
        {
            _data->window.draw( _landSprites.at( i ) );
        };
    }
}










