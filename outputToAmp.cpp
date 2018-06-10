/*
Copyright (C) 2011 Georgia Institute of Technology

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A mARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

/*
* Generates square pulse current commands.
*/

#include <outputToAmp.h>

extern "C" Plugin::Object *createRTXIPlugin(void) {
	return new OtoA();
}

static DefaultGUIModel::variable_t vars[] =
{
	{ "IAInput", "", DefaultGUIModel::INPUT, },
	{ "Ia_Act_Input", "", DefaultGUIModel::INPUT, },
	{ "Output_To_Amp", "", DefaultGUIModel::OUTPUT, },
	{ "Toggle_Output","0=Live / 1 = Model", DefaultGUIModel::PARAMETER },
};

static size_t num_vars = sizeof(vars) / sizeof(DefaultGUIModel::variable_t);

OtoA::OtoA(void) : DefaultGUIModel("Output to Amp", ::vars, ::num_vars) {
	setWhatsThis("<p><b>I-Step:</b><br>This module sums input from IA_Calc and ia-activate and sends one output to the amplifier.</p>");
	createGUI(vars, num_vars);
	update(INIT);
	refresh();
	resizeMe();
}

OtoA::~OtoA(void) {}

void OtoA::execute(void) {
	IA_Input = input(0); 
	Ia_Act_Input = input(1); //protocol input is in mV

	if (Toggle_Output==1) // For M_Neuron
	{  
		Ia_Act_Input = Ia_Act_Input * 2; //scale protocol input to V 
	}

	output(0) = Ia_Act_Input+IA_Input;
		

}

void OtoA::update(DefaultGUIModel::update_flags_t flag) {
	switch (flag) {
		case INIT:
			setParameter("Toggle_Output", QString::number(0));

			break;

		case MODIFY:
			Toggle_Output = getParameter("Toggle_Output").toInt();
			break;

		case PAUSE:
			output(0) = 0;
	
		case PERIOD:
	
		default:
			break;
	}
		
}
