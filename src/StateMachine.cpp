#include "StateMachine.hpp"

//StateMachine käsittelee tietoa kaikista tiloista, mitä pelissä on. Esim. Pause, Resume, Menu, GameMode jne...
//ja prosessoi niitä, käyttäjän käskyjen mukaan
namespace Hills
{

	//Lisätään uusi tila StateMachineen antamalla ensin true sille tiedolle, että uusi tila tullaan nyt lisäämään
	//sitten kerrotaan korvaako uusi tila vanhan tilan.
	//Lopulta liikutetaan muistista uusi tila (unique_ptr) std::movella StateMachineen, mutta stackiin sitä ei vielä
	//lisätä. Huom! koska unique_ptr, niin käytetään std::movea, sillä unique_ptr:ää ei voi kopioida.
	//Käytännössä siis muistin sisältö (_newState) siirretään StateMachinelle sopivampaan paikkaan mustissa, jotta
	//StateMachine pääsee siihen nyt käsiksi.

	void StateMachine::AddState( StateRef newState, bool isReplacing )
	{
		this->_isAdding = true;
		this->_isReplacing = isReplacing;
		this->_newState = std::move( newState );
	}

	//Kerrotaan StateMachinelle, että nykyinen tila tullaan poistamaan stackista.

	void StateMachine::RemoveState()
	{
		this->_isRemoving = true;
	}

	//Kun yllä olevat funktiot on suoritettu tapahtuu itse tilojen prosessointi. Nyt kun StateMachinen boolean-
	//arvoja on kopeloitu, niin tapahtuu tilojen prosessointi sen perusteella mitä arvoja on saatu.
	//Tämä seuraava funktio toteutetaan siis aina heti jommankumman ylemmän funktion jälkeen gameloopissa.
	//Funktio suorittaa operaatiot StateMachinen stack<StateRef>-listaan.

	void StateMachine::ProcessStateChanges()
	{

		//Jos tila halutaan poistaa kokonaan listasta ja tiloja sisältävä stack-lista sisältää väh. yhden tilan
		//niin poistetaan päällimmäinen tila. Tämä suoritetaan jos gameloopissa käytetään StateMachine::RemoveState()-
		//funktiota

		if ( this->_isRemoving && !this->_states.empty() )
		{
			this->_states.pop();

			//Jos StateMachinen tilalista (std::stack<StateRef>) ei edelleenkään poiston jälkeen ole tyhjä
			//otetaan listan ylin (viimeinen) StateRef-elementti haltuun ja kerrotaan sille, että jatkaa tekemistään
			//nyt kuitenkin meille näkyvänä, sillä se on "top-state" tässä vaiheessa.

			if ( !this->_states.empty() )
			{
				this->_states.top()->Resume();
			}

			//Ei haluta poistaa enempää tiloja stackista. (Poistetaan aina yksi kerrallaan).

			this->_isRemoving = false;
		}

		//Jos tilaa ei haluttu poistaa, eli gameloopissa käytettiinkin StateMachine::AddState( )-funktiota,
		//siirrytään uuden tilan lisäykseen.

		if ( this->_isAdding )
		{

			//Mikäli Stack ei ole tyhjä-->

			if( !this->_states.empty() )
			{

				//Mikäli nykyinen tila tullaan korvaamaan _isReplacing = true
				//voidaan suosiolla poistaa päällimmäinen tila, joka on näkyvillä meille

				if ( !this->_isReplacing )
				{
					this->_states.pop();
				}

				//Jos ei haluta korvata, on kyseessa Pause, eli laitetaan Pause-tila vain nykytilan päälle
				//poistamatta sitä.

				else
				{
					this->_states.top()->Pause();
				}
			}

			//Kun tiedetään oliko tila vain Pause vai haluttiinko uusi tila korvata kokonaan (esim menusta --> peliin
			//Menu-tila halutaan korvata peli-tilalla) siirretään päällimmäiseksi tilaksi _newState (unique_ptr) ja
			//alustetaan tämä tila, joka juuri lisättiin stacckiin. Tämän jälkeen _isAdding falseksi.

			this->_states.push( std::move(this->_newState) );
			this->_states.top()->Init();
			this->_isAdding = false;
		}
	}

	//lopulta kun tilat on prosessoitu ylläolevan funktion avulla, niin gameloopissa kutsutaan StateMachinen
	//GetActiveState()-funktiota joka yksinkertaisesti palauttaa stackin päällimmäisen tilan.

	StateRef &StateMachine::GetActiveState()
	{
		return this->_states.top();
	}
}
