#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class MainHero
{
public:
	virtual void Fight() {}
};

class Bestiariy : public MainHero
{
public:

	void Fight() override
	{
		cout << "\t\t\t\t\t\t\tБестиарий";
	}
};

class Frakiec : public MainHero
{
public:

	void Fight() override
	{
		cout << "\t\t\t\t\t\t\tФракиец ";
	}
};

class Mirmilon : public MainHero
{
public:

	void Fight() override
	{
		cout << "\t\t\t\t\t\t\tМирмилон";
	}
};

class Ekvit : public MainHero
{
public:

	void Fight() override
	{
		cout << "\t\t\t\t\t\t\tЭквит ";
	}
};

class Gall : public MainHero
{
public:

	void Fight() override
	{
		cout << "\t\t\t\t\t\t\tГалл ";
	}
};

class Creator
{
public:
	virtual MainHero* createMainHero() const = 0;

	void SomeOperation()
	{
		MainHero* mainhero = this->createMainHero();

		mainhero->Fight();
	}
};

class ConcreteBestiariy : public Creator
{
public:

	MainHero* createMainHero() const override
	{
		return new Bestiariy();
	}
};

class ConcreteFrakiec : public Creator
{
	MainHero* createMainHero() const override
	{
		return new Frakiec();
	}
};

class ConcreteMirmilon : public Creator
{
	MainHero* createMainHero()const override
	{
		return new Mirmilon();
	}
};

class ConcreteEkvit : public Creator
{
	MainHero* createMainHero() const override
	{
		return new Ekvit();
	}
};

class ConcreteGall : public Creator
{
	MainHero* createMainHero() const override
	{
		return new Gall();
	}
};

class Enemy
{
public:
	virtual void Fight() {}
};

class Lion : public Enemy
{
public:

	void Fight() override
	{
		cout << "\tЛев" << endl;
	}
};

class Tiger : public Enemy
{
public:

	void Fight() override
	{
		cout << "\tТигр" << endl;
	}
};

class Bear : public Enemy
{
public:

	void Fight() override
	{
		cout << "\tМедведь" << endl;
	}
};

class Leopard : public Enemy
{
public:

	void Fight() override
	{
		cout << "\tЛеопард" << endl;
	}
};

class EnemyCreator
{
public:
	virtual Enemy* createEnemy() const = 0;

	void SomeOperation()
	{
		Enemy* enemy = this->createEnemy();

		enemy->Fight();
	}
};

class ConcreteLion : public EnemyCreator
{
public:

	Enemy* createEnemy() const override
	{
		return new Lion();
	}
};

class ConcreteTiger : public EnemyCreator
{
public:

	Enemy* createEnemy() const override
	{
		return new Tiger();
	}
};

class ConcreteBear : public EnemyCreator
{
public:

	Enemy* createEnemy() const override
	{
		return new Bear();
	}
};

class ConcreteLeopard : public EnemyCreator
{
public:

	Enemy* createEnemy() const override
	{
		return new Leopard();
	}
};

class MainHeroEquipment
{
public:

	vector<string> equipment_parts;

	void PrintEquipment()
	{
		cout << "(";

		for (int i = 0; i < equipment_parts.size(); i++)
		{
			if (equipment_parts[i] == equipment_parts.back())
			{
				cout << equipment_parts[i] << ")" << endl;
			}
			else
			{
				cout << equipment_parts[i] << ",";
			}
		}

		cout << endl << endl;
	}
};

class Builder
{
public:

	virtual ~Builder() {}
	virtual void buildSword() const = 0;
	virtual void buildSpear() const = 0;
	virtual void buildShield() const = 0;
	virtual void buildArmor() const = 0;
};

class EquipmentBuilder : public Builder
{
	MainHeroEquipment* equipment;

public:

	EquipmentBuilder()
	{
		this->Reset();
	}

	~EquipmentBuilder()
	{
		delete equipment;
	}

	void Reset()
	{
		this->equipment = new MainHeroEquipment();
	}

	void buildSword()const override {
		this->equipment->equipment_parts.push_back("Меч");
	}

	void buildSpear()const override {
		this->equipment->equipment_parts.push_back("Копье");
	}

	void buildShield()const override {
		this->equipment->equipment_parts.push_back("Щит");
	}

	void buildArmor()const override {
		this->equipment->equipment_parts.push_back("Доспехи");
	}

	MainHeroEquipment* getEquipment()
	{
		MainHeroEquipment* result = this->equipment;
		this->Reset();

		return result;
	}
};

class Director
{
	Builder* builder;

public:

	void set_builder(Builder* builder)
	{
		this->builder = builder;
	}

	void BuildForEasyLvl()
	{
		this->builder->buildArmor();
		this->builder->buildShield();
		this->builder->buildSpear();
		this->builder->buildSword();
	}

	void BuildForNormalLvl()
	{
		this->builder->buildArmor();
		this->builder->buildShield();
		this->builder->buildSword();
	}

	void BuildForHardLvl()
	{
		this->builder->buildArmor();
		this->builder->buildSpear();
		this->builder->buildSword();
	}
};

class Game
{
public:

	void playGame()
	{
		//выбор героя
		int choise;
		cout << "Выберите героя:" << endl << endl;
		cout << "Бестиарий - 1\nФракиец - 2\nМирмилон - 3\nЭквит - 4\nГалл - 5\n\n";
		cin >> choise;

		Creator* mainhero = new ConcreteBestiariy();

		switch (choise)
		{
		case 1:
			mainhero = new ConcreteBestiariy();
			break;

		case 2:
			mainhero = new ConcreteFrakiec();
			break;

		case 3:
			mainhero = new ConcreteMirmilon();
			break;

		case 4:
			mainhero = new ConcreteEkvit();
			break;

		case 5:
			mainhero = new ConcreteGall();
			break;

		default:
			cout << "Неверный выбор героя!" << endl;
			break;
		}


		//выбор уровня сложности(от него зависит снаряжение героя)
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		EquipmentBuilder* builder = new EquipmentBuilder();
		Director* direktor = new Director();
		direktor->set_builder(builder);
		MainHeroEquipment* equipment = new MainHeroEquipment();

		cout << "\nВыберите уровень сложности:" << endl;

		cout << "Легкий - 1\nСредний - 2\nСложный - 3\n\n";
		cin >> choise;

		switch (choise)
		{
		case 1:
			direktor->BuildForEasyLvl();
			equipment = builder->getEquipment();
			break;

		case 2:
			direktor->BuildForNormalLvl();
			equipment = builder->getEquipment();
			break;

		case 3:
			direktor->BuildForHardLvl();
			equipment = builder->getEquipment();
			break;

		default:
			cout << "Неверный выбор уровня сложности!\n";
			break;
		}

		//случайное создание противника
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
		choise = 1 + rand() % 4;

		EnemyCreator* enemy = new ConcreteLion();

		switch (choise)
		{
		case 1:
			enemy = new ConcreteLion();
			break;

		case 2:
			enemy = new ConcreteTiger();
			break;

		case 3:
			enemy = new ConcreteBear();
			break;

		case 4:
			enemy = new ConcreteLeopard();
			break;
		}

		//битва
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		cout << "\t\t\t\t\t\t\tБИТВА НАЧАЛАСЬ!" << endl;
		cout << "========================================================================================================================";

		mainhero->SomeOperation();
		cout << "\tVS";
		enemy->SomeOperation();

		cout << "\t\t\t";
		equipment->PrintEquipment();


		delete mainhero;
		delete enemy;
		delete equipment;
		delete builder;
		delete direktor;
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	Game game;
	game.playGame();

	return 0;
}