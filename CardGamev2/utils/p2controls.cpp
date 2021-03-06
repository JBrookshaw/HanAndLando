// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

#include "p2controls.hpp"

glm::mat4 P1_CARD1;
glm::mat4 P1_CARD2;
glm::mat4 P1_CARD3;

glm::mat4 P2_CARD1;
glm::mat4 P2_CARD2;
glm::mat4 P2_CARD3;

glm::mat4 P1_CARD1Copy;
glm::mat4 P1_CARD2Copy;
glm::mat4 P1_CARD3Copy;

glm::mat4 P2_CARD1Copy;
glm::mat4 P2_CARD2Copy;
glm::mat4 P2_CARD3Copy;

glm::mat4 my_ScalingMatrix2 = glm::scale(0.8f, 1.0f ,0.8f);
glm::mat4 my_ScalingMatrix3 = glm::scale(0.95f, 1.0f ,0.95f);

glm::mat4 my_Matrix = glm::translate(0.0f, 0.0f, -0.05f);

glm::mat4 selected_Card = glm::translate(0.0f, 1.5f, 0.0f);

mat4 rotation_ = mat4(
	vec4( cos(3.14), 0.0,  sin(3.14),  0.0),
	vec4(0.0,  1.0, 0.0, 0.0),
	vec4(-sin(3.14), 0.0,  cos(3.14),  0.0),
	vec4( 0.0, 0.0, 0.0, 1.0)
	);

mat4 rotation_2 = mat4(
	vec4( cos(0.2), 0.0,  sin(0.2),  0.0),
	vec4(0.0,  1.0, 0.0, 0.0),
	vec4(-sin(0.2), 0.0,  cos(0.2),  0.0),
	vec4( 0.0, 0.0, 0.0, 1.0)
	);

mat4 die_Animation = my_ScalingMatrix3*rotation_2;


bool p1card3dead1 = false; //Tex2
bool p1card2dead1 = false; //Tex6
bool p1card1dead1 = false; //Tex3


void resetDeadFlags2(){
p1card3dead1 = false; //Tex1
p1card2dead1 = false; //Tex6
p1card1dead1 = false; //Tex3

}

bool getP1Card3Dead(){
	return p1card3dead1;
}
bool getP1Card2Dead(){
	return p1card2dead1;
}
bool getP1Card1Dead(){
	return p1card1dead1;
}

void setP1Card3Dead(){
	p1card3dead1 = false;
}
void setP1Card2Dead(){
	p1card2dead1 = false;
}
void setP1Card1Dead(){
	p1card1dead1 = false;
}

//false = player1 | true = player2
int player1 = 20;
int moves1 = 0;
bool turn2 = false;
bool p2attacking = false;
float my_Distance = 60, my_Distance2 =60, my_Distance3 = 60, my_Distance4= 60;

bool attack_right = false, attack_left = false, attack_middle = false, attack_player = false;
bool die_ = false, die_2 = false, die_3 = false,	die_4 = false;
bool p2card1selected = false, p2card2selected = false, p2card3selected  = false;
bool p2card1selectedanimation = false, p2card2selectedanimation = false, p2card3selectedanimation  = false;

int p2Moves() {

	return moves1;
}

void p2Zero() {

	moves1 = 0;
}

void p1Loss(int loss1) {

	player1 = player1 - loss1;

}

void p1LifeSet(int set1) {

	player1 = set1;

}

int p1Life() {

	return player1;

}


void player2Inputs(){

	readInputs_();

	player2Selection();

	if(p2card1selected){
		p2card1attack();
	}
	else if(p2card3selected)
	{
		p2card3attack();
	}
		else if(p2card2selected)
	{
		p2card2attack();
	}

}

void rev2() {

	if(!p1card1dead1){
	P1_CARD1 = P1_CARD1Copy;
	}
	if(!p1card2dead1){
	P1_CARD2 = P1_CARD2Copy;
	}
	if(!p1card3dead1){
	P1_CARD3 = P1_CARD3Copy;
	}

}

void p2card1attack(){

	if(!attack_right && attack_left && !attack_middle && !attack_player){
		P2_CARD1 = glm::translate(P2_CARD1, glm::vec3(0.0f, 0.0f, -0.08f));
		my_Distance--;
		if(my_Distance <= 0){
			P2_CARD1 = P2_CARD1Copy;
			attack_left = false;
			my_Distance = 60;
			die_=true;
		}
	}
	if(die_){
		P1_CARD3 = P1_CARD3 * die_Animation;
		my_Distance--;
		if(my_Distance <= 0){
			p1card3dead1 = true;//P1_CARD3 = P1_CARD3Copy;
			die_ = false;
			my_Distance=60;
			p2card1selectedanimation = false;
			p2card1selected =false;
			p2attacking = false;
			moves1++;
		}
	}
	if(attack_right && !attack_left && !attack_middle && !attack_player){
		P2_CARD1 = glm::translate(P2_CARD1, glm::vec3(0.12f, 0.0f, -0.08f));
		my_Distance2--;
		if(my_Distance2 <= 0){
			P2_CARD1 = P2_CARD1Copy;
			attack_right = false;
			my_Distance2 = 60;
			die_2=true;
		}
	}
	if(die_2){
		P1_CARD1 = P1_CARD1 * die_Animation;
		my_Distance2--;
		if(my_Distance2 <= 0){
			p1card1dead1 = true;//P1_CARD1 = P1_CARD1Copy;
			die_2 = false;
			my_Distance2=60;
			 p2card1selectedanimation = false;
			p2card1selected =false;
			p2attacking = false;
			moves1++;
			
		}
	}

	if(!attack_right && !attack_left && attack_middle && !attack_player){
		P2_CARD1 = glm::translate(P2_CARD1, glm::vec3(0.06f, 0.0f, -0.08f));
		my_Distance3--;
		if(my_Distance3 <= 0){
			P2_CARD1 = P2_CARD1Copy;
			attack_middle = false;
			my_Distance3 = 60;
			die_3=true;
		}
	}
	if(die_3){
		P1_CARD2 = P1_CARD2 * die_Animation;
		my_Distance3--;
		if(my_Distance3 <= 0){
			p1card2dead1 = true;//P1_CARD2 = P1_CARD2Copy;
			die_3 = false;
			my_Distance3=60;
			 p2card1selectedanimation = false;
			p2card1selected =false;
			p2attacking = false;
			moves1++;
			
		}
	}
	if(!attack_right && !attack_left && !attack_middle && attack_player){
		P2_CARD1 = glm::translate(P2_CARD1, glm::vec3(0.06f, 0.0f, -0.19f)); //Third Number Adjusted to .09 from .05
		my_Distance4--;
		if(my_Distance4 <= 0){
			P2_CARD1 = P2_CARD1Copy;
			attack_player = false;
			my_Distance4 = 60;
			die_4=true;
		}
	}
	if(die_4){
		//P1_CARD1 = P1_CARD1 * die_Animation; // Changed to life subtraction
		my_Distance4--;
		if(my_Distance4 <= 0){
			p1Loss(2);		// Life Subtraction
			die_4 = false;
			my_Distance4=60;
			 p2card1selectedanimation = false;
			p2card1selected =false;
			p2attacking = false;
			moves1++;
			
		}
	}
	
}

void p2card2attack(){

	if(!attack_right && !attack_left && attack_middle && !attack_player){
		P2_CARD2 = glm::translate(P2_CARD2, glm::vec3(0.0f, 0.0f, -0.05f));
		my_Distance--;
		if(my_Distance <= 0){
			P2_CARD2 = P2_CARD2Copy;
			attack_middle = false;
			my_Distance = 60;
			die_=true;
		}
	}
	if(die_){
		P1_CARD2 = P1_CARD2 * die_Animation;
		my_Distance--;
		if(my_Distance <= 0){
			p1card2dead1 = true;//P1_CARD2 = P1_CARD2Copy;
			die_ = false;
			my_Distance=60;
			p2card2selectedanimation = false;
			p2card2selected =false;
			p2attacking = false;
			moves1++;
		}
	}
	if(attack_right && !attack_left && !attack_middle && !attack_player){
		P2_CARD2 = glm::translate(P2_CARD2, glm::vec3(0.06f, 0.0f, -0.05f));
		my_Distance2--;
		if(my_Distance2 <= 0){
			P2_CARD2 = P2_CARD2Copy;
			attack_right = false;
			my_Distance2 = 60;
			die_2=true;
		}
	}
	if(die_2){
		P1_CARD1 = P1_CARD1 * die_Animation;
		my_Distance2--;
		if(my_Distance2 <= 0){
			p1card1dead1 = true;//P1_CARD1 = P1_CARD1Copy;
			die_2 = false;
			my_Distance2=60;
			 p2card2selectedanimation = false;
			p2card2selected =false;
			p2attacking = false;
			moves1++;
			
		}
	}

	if(!attack_right && attack_left && !attack_middle && !attack_player){
		P2_CARD2 = glm::translate(P2_CARD2, glm::vec3(-0.06f, 0.0f, -0.05f));
		my_Distance3--;
		if(my_Distance3 <= 0){
			P2_CARD2 = P2_CARD2Copy;
			attack_left = false;
			my_Distance3 = 60;
			die_3=true;
		}
	}
	if(die_3){
		P1_CARD3 = P1_CARD3 * die_Animation;
		my_Distance3--;
		if(my_Distance3 <= 0){
			p1card3dead1 = true;//P1_CARD3 = P1_CARD3Copy;
			die_3 = false;
			my_Distance3=60;
			p2card2selectedanimation = false;
			p2card2selected =false;
			p2attacking = false;
			moves1++;
			
		}
	}
if(!attack_right && !attack_left && !attack_middle && attack_player){
		P2_CARD2 = glm::translate(P2_CARD2, glm::vec3(0.0f, 0.0f, -0.19f)); // ADJusted to middle back
		my_Distance4--;
		if(my_Distance4 <= 0){
			P2_CARD2 = P2_CARD2Copy;
			attack_player = false;
			my_Distance4 = 60;
			die_4=true;
		}
	}
	if(die_4){
		//P1_CARD1 = P1_CARD1 * die_Animation; // Changed to life subtraction
		my_Distance4--;
		if(my_Distance4 <= 0){
			p1Loss(2);		// Life Subtraction
			die_4 = false;
			my_Distance4=60;
			 p2card2selectedanimation = false;
			p2card2selected =false;
			p2attacking = false;
			moves1++;
		}
	}
	
}

void p2card3attack(){

	if(attack_right && !attack_left && !attack_middle && !attack_player){
		P2_CARD3 = glm::translate(P2_CARD3, glm::vec3(0.0f, 0.0f, -0.08f));
		my_Distance--;
		if(my_Distance <= 0){
			P2_CARD3 = P2_CARD3Copy;
			attack_right = false;
			my_Distance = 60;
			die_=true;
		}
	}
	if(die_){
		P1_CARD1 = P1_CARD1 * die_Animation;
		my_Distance--;
		if(my_Distance <= 0){
			p1card1dead1 = true;//P1_CARD1 = P1_CARD1Copy;
			die_ = false;
			my_Distance=60;
			 p2card3selectedanimation = false;
			p2card3selected =false;
			p2attacking = false;
			moves1++;
		}
	}
	if(!attack_right && attack_left && !attack_middle && !attack_player){
		P2_CARD3 = glm::translate(P2_CARD3, glm::vec3(-0.12f, 0.0f, -0.08f));
		my_Distance2--;
		if(my_Distance2 <= 0){
			P2_CARD3 = P2_CARD3Copy;
			attack_left = false;
			my_Distance2 = 60;
			die_2=true;
		}
	}
	if(die_2){
		P1_CARD3 = P1_CARD3 * die_Animation;
		my_Distance2--;
		if(my_Distance2 <= 0){
			p1card3dead1 = true;//P1_CARD3 = P1_CARD3Copy;
			die_2 = false;
			my_Distance2=60;
			 p2card3selectedanimation = false;
			p2card3selected =false;
			p2attacking = false;
			moves1++;
		}
	}

	if(!attack_right && !attack_left && attack_middle && !attack_player){
		P2_CARD3 = glm::translate(P2_CARD3, glm::vec3(-0.06f, 0.0f, -0.08f));
		my_Distance3--;
		if(my_Distance3 <= 0){
			P2_CARD3 = P2_CARD3Copy;
			attack_middle = false;
			my_Distance3 = 60;
			die_3=true;
		}
	}
	if(die_3){
		P1_CARD2 = P1_CARD2 * die_Animation;
		my_Distance3--;
		if(my_Distance3 <= 0){
			p1card2dead1 = true;//P1_CARD2 = P1_CARD2Copy;
			die_3 = false;
			my_Distance3=60;
			 p2card3selectedanimation = false;
			p2card3selected =false;
			p2attacking = false;
			moves1++;
		}
	}
if(!attack_right && !attack_left && !attack_middle && attack_player){
		P2_CARD3 = glm::translate(P2_CARD3, glm::vec3(-0.06f, 0.0f, -0.19f)); // Adjusted third number to .09
		my_Distance4--;
		if(my_Distance4 <= 0){
			P2_CARD3 = P2_CARD3Copy;
			attack_player = false;
			my_Distance4 = 60;
			die_4=true;
		}
	}
	if(die_4){
		//P1_CARD1 = P1_CARD1 * die_Animation; // Changed to life subtraction
		my_Distance4--;
		if(my_Distance4 <= 0){
			p1Loss(2);		// Life Subtraction
			die_4 = false;
			my_Distance4=60;
			 p2card3selectedanimation = false;
			p2card3selected =false;
			p2attacking = false;
			moves1++;
		}
	}
	
}

void player2Selection(){
	if(!p2card1selectedanimation && p2card1selected)
	{
		P2_CARD1 = P2_CARD1 * selected_Card;
		p2card1selectedanimation=true;
		p2card2selectedanimation=false;
		p2card3selectedanimation=false;

		p2card2selected = false;
		p2card3selected = false;
		P2_CARD2 = P2_CARD2Copy;
		P2_CARD3 = P2_CARD3Copy;
	}
	if(!p2card2selectedanimation && p2card2selected)
	{
		P2_CARD2 = P2_CARD2 * selected_Card;

		p2card1selectedanimation=false;
		p2card2selectedanimation=true;
		p2card3selectedanimation=false;

		p2card1selected = false;
		p2card3selected = false;
		P2_CARD1 = P2_CARD1Copy;
		P2_CARD3 = P2_CARD3Copy;
	}
	if(!p2card3selectedanimation && p2card3selected)
	{

		P2_CARD3 = P2_CARD3 * selected_Card;

		p2card1selectedanimation=false;
		p2card2selectedanimation=false;
		p2card3selectedanimation=true;

		p2card1selected = false;
		p2card2selected = false;

		P2_CARD2 = P2_CARD2Copy;
		P2_CARD1 = P2_CARD1Copy;
	}
}

void createCopys_(){
	P1_CARD1Copy = P1_CARD1;
	P1_CARD2Copy = P1_CARD2;
	P1_CARD3Copy = P1_CARD3;

	P2_CARD1Copy = P2_CARD1;
	P2_CARD2Copy = P2_CARD2;
	P2_CARD3Copy = P2_CARD3;
}

void readInputs_(){
	bool isCardSelected = p2card1selected || p2card2selected || p2card3selected;
	if(!p2attacking) {
		if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS && isCardSelected){
			attack_right = true;
			attack_left=false;
			attack_middle =false;
			attack_player = false;

			p2attacking = true;
			
		}
		else	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS && isCardSelected){
			attack_right = false;
			attack_left=true;
			attack_middle =false;
			attack_player = false;
			p2attacking = true;
			
		}
		else	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS && isCardSelected){
			attack_right = false;
			attack_left=false;
			attack_middle =true;
			attack_player = false;
			p2attacking = true;
			
		}
		else	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS && isCardSelected){
			attack_right = false;
			attack_left=false;
			attack_middle =false;
			attack_player = true;
			p2attacking = true;
			

		}

	if (glfwGetKey( window, GLFW_KEY_1 ) == GLFW_PRESS){
		p2card1selected = true;
	}
	else	if (glfwGetKey( window, GLFW_KEY_2 ) == GLFW_PRESS){
		p2card2selected = true;
	}
	else	if (glfwGetKey( window, GLFW_KEY_3 ) == GLFW_PRESS){
		p2card3selected = true;
	}
	}//end if attacking
}

glm::mat4 getP1_Card1(){
	return P1_CARD1;
}
glm::mat4 getP1_Card2(){
	return P1_CARD2;
}
glm::mat4 getP1_Card3(){
	return P1_CARD3;
}
glm::mat4 getP2_Card1(){
	return P2_CARD1;
}
glm::mat4 getP2_Card2(){
	return P2_CARD2;
}
glm::mat4 getP2_Card3(){
	return P2_CARD3;
}

void  setP1_Card1(glm::mat4 model){
	P1_CARD1 = model;
}
void  setP1_Card2(glm::mat4 model){
	P1_CARD2 = model;
}
void  setP1_Card3(glm::mat4 model){
	P1_CARD3 = model;
}
void  setP2_Card1(glm::mat4 model){
	P2_CARD1 = model;
}
void  setP2_Card2(glm::mat4 model){
	P2_CARD2 = model;
}
void  setP2_Card3(glm::mat4 model){
	P2_CARD3 = model;
}