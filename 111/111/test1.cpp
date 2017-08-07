
#include <cstdio>
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <string>

#include "LorentzTable.h"
#include "Vector.h"

/**
* Runs the lorentz table simulation. Random args not available. Data output to
* 'loreout.dat'.
*
* int n: iterations of the simulation to run.
*/
void RunLorentz(int n);
/**
* InnerRun is called iternally by each of the Run functions, and performs the
* actual simulation once table and initial conditions have been initialised.
* It takes in all the necessary components of the simulation, including the
* number of iterations plus a file to output data to.
*
* Once this function has run the Vector position will contain the final
* position of the ball, and velocity conatins its final velocity.
*
* ITable & table: billiard table for the simulation.
* Vector & position: initial position of the billiard ball.
* Vector & velocity: initial velocity of the billiard ball.
* int n: number of iterations for the simulation.
* FILE * file: file stream to write to.
*/
void InnerRun(ITable & table, Vector & position, Vector & velocity, int n, FILE * file);

/**
* Initialises vector position and velocity of the billiard ball, by asking
* for user input. initial and velocity will contain the values once the
* function has run.
*
* Vector & initial: Vector to store initial position in.
* Vector & velocity: Vector to store initial velocity in.
*/
void GetArgs(Vector & initial, Vector & velocity);

/**
* Function to randomise initial conditions for a given table type with
* supplied parameters. initial and velocity will contain the values once the
* function has run.
*
* The type of billiard table must be specified using the parameter type. The
* three options are: 1=circular 2= elliptical 3=rectangular 4=stadium 5=lorentz. The
* parameter params must contain the necessary number of parameters defining
* the geometry of the table. For the rectangular and stadium tables this is
* an array with two values, for the circular table just one and three for the
* elliptical and lorentz tables.
*
* Vector & initial: Vector to store initial position in.
* Vector & velocity: Vector to store initial velocity in.
* int type: integer 1-5 specifying the type of table to generate values for.
* double params[]: array specifying the geometry of the table.
*/
void RandomArgs(Vector & initial, Vector & velocity, double params[]);


int main()
{
	int n = 10;
	RunLorentz(n);
}


void RunLorentz(int n)
{
	//As in previous run functions:
	double y = 120;
	double x = 63.5;
	double r = 60;
	

	LorentzTable table = LorentzTable(x, y, r);

	Vector initial, velocity;

	int choice;

	printf("\n# Initial Conditions: #\nEnter 1 for random initial coniditions, and 0 for user-input: ");

	//Choose random of specified arguments.
	while (!(std::cin >> choice))
	{
		std::cin.clear();
		std::cin.ignore();
		printf("Please enter a valid choice: ");
	}

	if (choice)
	{
		//Table parameters stored in array to be passed to the random
		//initial condition generator.
		double params[3] = { x, y, r };
		//Randomly generate based on table parameters.
		RandomArgs(initial, velocity, params);
	}
	else
	{
		//Otherwise ask for user arguments.
		GetArgs(initial, velocity);
	}

	//GetArgs(initial, velocity);

	FILE * file;

	fopen_s(&file, "loreout.dat", "w");

	printf("\nWriting to 'loreout.dat'...\n");

	InnerRun(table, initial, velocity, n, file);

	fclose(file);

	printf("Done!\n");

	return;
}
void RandomArgs(Vector & initial, Vector & velocity, double params[])
{
	//Initialise the random engine.
	std::default_random_engine engine;
	engine.seed(std::time(0));

	//Temporary doubles to store output.
	double temp, iX, iY;
	//Ranges specified by x and y lengths of rectangle.
	std::uniform_real_distribution<double> rangeX(-params[0], params[0]);
	std::uniform_real_distribution<double> rangeY(-params[1], params[1]);
	//Get random values.
	iX = rangeX(engine);
	iY = rangeY(engine);

	//Put generated position values in initial vector.
	initial.fX = iX;
	initial.fY = iY;

	//Velocity is randomised, but less constraint required.
	velocity = Vector(0.0, 0.0);
	std::uniform_real_distribution<double> rangeV(-1, 1);

	//Require at least one velocity component to be non-zero.
	while (velocity.fX == 0.0 && velocity.fY == 0.0)
	{
		velocity.fX = rangeV(engine);
		velocity.fY = rangeV(engine);
	}

	return;
}

void InnerRun(ITable & table, Vector & position, Vector & velocity, int n, FILE * file)
{
	//Get initial angle.
	double angle = velocity.Arg();

	//Print headers to file.
	fprintf(file, "%-3s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n", "i", "x", "y", "mp", "pa", "a", "vx", "vy", "mv", "va");

	//For specified number of iterations:
	for (int i = 0; i != n; i++)
	{
		//Print current status.
		fprintf(file, "%-3i%-10.6f%-10.6f%-10.6f%-10.6f%-10.6f%-10.6f%-10.6f%-10.6f%-10.6f\n",
			i, position.fX, position.fY, position.Mod(), position.Arg(),
			angle, velocity.fX, velocity.fY, velocity.Mod(), velocity.Arg());
		//Find next position.
		position = table.CollisionPoint(position, velocity);
		//Find angle between table wall and ball trajectory.
		angle = std::fmod(table.AngleIncidence(position, velocity), 2 * M_PI);
		//Find velocity after collision.
		velocity = table.ReflectVector(position, velocity);
	}
}

void GetArgs(Vector & initial, Vector & velocity)
{
	//Doubles to store input.
	double iX, iY, vX, vY;

	//Get input:
	printf("Please enter initial x: ");
	std::cin >> iX;
	printf("Initial y: ");
	std::cin >> iY;
	printf("Initial x velocity: ");
	std::cin >> vX;
	printf("Initial y velocity: ");
	std::cin >> vY;

	//Store input in vectors.
	initial = Vector(iX, iY);
	velocity = Vector(vX, vY);

	return;
}
