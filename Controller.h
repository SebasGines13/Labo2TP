#pragma once
class Controller
{	
	private:
		bool _buttons[8];  /// Izquierda, derecha, arriba, abajo, botones
	public:
		enum class Buttons {
			Up, Down, Left, Right, ButtonShoot, ButtonMute, ButtonLess, ButtonMore
		};
		/// Métodos
		void reset(); /// para reiniciar el estado de los botones presionados.
		void push(Controller::Buttons button);
		bool isPressed(Controller::Buttons button);
};

