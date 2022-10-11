#include "City.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <regex>
#include <cmath>
using namespace std;

void City::count_harvest()
{
	harvest_per_acre = rand() % 6 + 1;

	float bushels_to_seed = seed_per_acre * cultivated_acres;
	bushels -= bushels_to_seed;

	bushel_harvest = cultivated_acres * harvest_per_acre;
	bushels = bushels + bushel_harvest;
}

void City::count_rats_damage()
{
	float max_damage = max_rat_damage * bushels;
	rats_damage = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / max_damage);
	bushels = bushels - rats_damage;
}

void City::count_population_deaths()
{
	int portions = bushels_to_eat / portion;
	if (population > portions)
	{
		bushels -= bushels_to_eat;
		dead = population - portions;
		float dead_percent = (float)dead / population;
		if (dead_percent > 0.45f || population == 0)
		{
			game_over();
		}
		population = portions;
	}
	else
	{
		bushels -= population * portion;
		dead = 0;
	}
}

void City::count_arrived()
{
	arrived = dead / 2 + (5 - harvest_per_acre) * bushels / 600 + 1;
	if (arrived < 0)
	{
		arrived = 0;
	}
	if (arrived > 50)
	{
		arrived = 50;
	}
	population += arrived;
}

void City::trade_acres()
{
	bushels -= acres_to_buy * acre_price;
	bushels += acres_to_cell * acre_price;
	acres += acres_to_buy;
	acres -= acres_to_cell;
}

void City::runner()
{
	while (year < 10)
	{
		++year;

		player_input();
		one_year();

		srand(time(0));
		acre_price = rand() % 10 + 17;

		if (bushels < 0)
			bushels = 0;
		count_statistics();
		print_round_statistics();
		input_to_save();
	}
	print_result();
	restart();
}

void City::print_round_statistics()
{
	cout << "Мой повелитель, соизволь поведать тебе" << endl;
	cout << "в году " << year << " твоего высочайшего правления" << endl;

	if (dead > 0)
	{
		cout << dead << " человек умерли с голоду";
		if (arrived > 0)
			cout << ", и ";
		else
			cout << endl;
	}

	if (arrived > 0)
		cout << arrived << " человек прибыли в наш великий город;" << endl;

	cout << "Население города сейчас составляет " << population << " человек;" << endl;
	
	if (plague)
		cout << "Чума уничтожила половину населения;" << endl;

	cout << "Мы собрали " << bushel_harvest << " бушелей пшеницы, по " << harvest_per_acre << " бушеля с акра;" << endl;
	cout << "Крысы истребили " << rats_damage << " бушелей пшеницы, оставив " << bushels << " бушеля в амбарах;" << endl;
	cout << "Город сейчас занимает " << acres << " акров;" << endl;
	cout << "1 акр земли стоит сейчас " << acre_price << " бушель." << endl;
}

void City::player_input()
{
	cout << "Что пожелаешь, повелитель?" << endl;
	cout << "Сколько акров земли повелеваешь купить? ";
	cin >> acres_to_buy;
	if (acres_to_buy * acre_price > bushels)
		input_warning();
	cout << endl;
	check_input(acres_to_buy);

	cout << "Сколько акров земли повелеваешь продать? ";
	cin >> acres_to_cell;
	if (acres_to_cell > acres)
		input_warning();
	cout << endl;
	check_input(acres_to_cell);

	cout << "Сколько бушелей пшеницы повелеваешь съесть? ";
	cin >> bushels_to_eat;
	if (bushels_to_eat > bushels)
		input_warning();
	cout << endl;
	check_input(bushels_to_eat);

	cout << "Сколько акров земли повелеваешь засеять? ";
	cin >> cultivated_acres;
	if (cultivated_acres > population * 10)
		input_warning();
	cout << endl;
	check_input(cultivated_acres);

	if (acres + acres_to_buy - acres_to_cell < cultivated_acres)
		input_warning(); // проверим, хватит ли нам акров земли
	if (bushels < bushels_to_eat + seed_per_acre * cultivated_acres + acres_to_buy * acre_price - acres_to_cell * acre_price)
		input_warning(); // проверим, хватит ли нам бушелей
}

void City::check_input(int input)
{
	if (input < 0)
	{
		cout << "Мой повелитель, количество должно быть неотрицательным" << endl;
		player_input();
	}
}

void City::input_warning()
{
	cout << endl;
	cout << "О, повелитель, пощади нас! У нас только " << population << " человек, ";
	cout << bushels << " бушелей пшеницы и " << acres << " акров земли!" << endl;
	player_input();
}

void City::check_plague()
{
	srand(time(0));
	float chance = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if (chance < 0.15)
	{
		plague = true;
		population = floor(population / 2);
	}
	else plague = false;
}

void City::one_year()
{
	trade_acres();

	count_harvest();
	count_rats_damage();

	count_population_deaths();
	count_arrived();
	check_plague();
}

void City::count_statistics()
{
	float dead_percent = (float)dead / population;
	P += dead_percent;
	int acres_per_citizen = acres / population;
	L += acres_per_citizen;
}

void City::print_result()
{
	P = P / ROUNDS;
	L = L / ROUNDS;
	if (P > 0.33 && L < 7)
	{
		cout << "Из-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас ";
		cout << "из города. Теперь вы вынуждены влачить жалкое существование в изгнании" << endl;
	}
	else if (P > 0.1 && L < 9)
	{
		cout << "Вы правили железной рукой, подобно Нерону и Ивану Грозному. Народ ";
		cout << "вздохнул с облегчением, и никто больше не желает видеть вас правителем" << endl;
	}
	else if (P > 0.03 && L < 10)
	{
		cout << "Вы справились вполне неплохо, у вас, конечно, есть недоброжелатели, ";
		cout << "но многие хотели бы увидеть вас во главе города снова" << endl;
	}
	else
		cout << "Фантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше" << endl;
}

void City::game_over()
{
	cout << "В городе осталось слишком мало жителей, чтобы работать" << endl;
	cout << "Ваше правление подошло к концу. Почему Вы были так жестоки к своему народу?.." << endl;
	cout << endl;

	restart();
}

void City::save_to_file()
{
	ofstream file(FILENAME);
	if (!file) return;

	file << "Год: " << year << endl;
	file << "Население: " << population << endl;
	file << "Акры земли: " << acres << endl;
	file << "Бушелей в амбарах: " << bushels << endl;;
	file << "Среднегодовой процент умерших: " << P << endl;
	file << "Количество акров на одного жителя: " << L << endl;
}

void City::read_from_file()
{
	ifstream file(FILENAME);
	if (!file) return;

	cout << "Продолжить игру? Y-yes, N-no ";
	char input = '-';
	while (input != 'Y' && input != 'N')
		cin >> input;
	cout << endl;

	if (input == 'Y')
	{
		string dummy;
		file >> dummy >> year;
		file >> dummy >> population;
		file >> dummy >> acres;
		file >> dummy >> bushels;
		file >> dummy >> P;
		file >> dummy >> L;
	}
	else
		restart();
}

void City::run_game()
{
	read_from_file();
	restart();
}

void City::input_to_save()
{
	cout << "Сохраниться в файл? Y-yes, N-no ";
	char input = '-';
	while (input != 'Y' && input != 'N')
		cin >> input;
	cout << endl;
	if (input == 'Y')
		save_to_file();
}

void City::restart()
{
	bushels = START_BUSHELS;
	acres = START_ACRES;
	population = START_POPULATION;
	P = 0;
	L = 0;
	year = 1;

	srand(time(0));

	cout << "Это 1 год Вашего правления в процветающем городе в долине Нила" << endl;
	cout << "На наших складах " << bushels << " бушелей пшеницы;" << endl;
	cout << "Наш город занимает " << acres << " акров;" << endl;
	cout << "В нашем городе живёт " << population << " человек;" << endl;
	acre_price = rand() % 10 + 17;
	cout << "Цена акра земли составляет " << acre_price  << " бушелей;" << endl;

	runner();
}