# Analysis-of-algorithms
A laboratory work of Analysis of algorithms (ITMO University)

# Hammurabi
## Task Formulation
### Game rules

The game consists of 10 rounds, during which the player, acting as the ruler of ancient Babylon Hammurabi, manages the resources of the city. Resources are: population, acres of land, and bushels of wheat. Each round represents one year of government. Each citizen cultivates a certain number of acres of land, resulting in the production of a certain number of bushels of wheat. This wheat can be used either as food for citizens (who die of starvation if there is a lack of food), or as seeds for sowing the next year's harvest. The player can also buy and sell land using wheat as currency.

Each round begins with the councilor's report, "My Lord, please tell me", on the current state of affairs in the city, consisting of last year's wheat harvest, the acres of land occupied by the city, and the change in population. After that, the advisor asks how much land needs to be bought or sold this year, how much wheat to use for seed, and how much wheat to use as food. The player answers these questions by entering integers.

The game hides some important information from the player: rules and coefficients for calculating parameters per round, but this is done intentionally. Selecting these parameters is part of the gameplay.

The game's variety is provided by a random number generator. The land price is determined randomly at the beginning of each round. It also randomly determines the number of bushels of wheat collected from each acre of land, the amount of wheat eaten by rats, and the number of new citizens who arrived in the city last year. Each year, there is some chance of a plague reducing the city's population by half.

The game ends after 10 rounds, or earlier if the entire population of the city dies out, or more than 45 percent of the population starves to death within one round.

### Algorithm

The game starts with the following parameters::

- The city has a population of 100 people
- There are 2,800 bushels of wheat in the city's bins
- The city covers 1,000 acres of land

At the beginning of each round, the player sees

- Round number
- The number of people who died of starvation (if not, then don't show it)
- The number of people who came to the city (if not, then don't show it)
- Whether there was a plague
- Current city population
- How much total wheat was harvested and how much wheat was obtained per acre
- How much wheat did the rats destroy
- How many acres does the city now occupy
- What is the price of one acre of land this year

The price of an acre is determined randomly at the beginning of each round from a range of 17 to 26

The player then enters:

- The number of acres of land that he wants to buy
- The number of acres of land that he wants to sell
- The number of bushels of wheat to be used as food
- The number of acres of land that need to be sown with wheat

The game monitors the values entered, and if the values turn out to be incorrect (for example, the amount of land that the player wants to buy cannot be paid for with the available wheat, or a negative number of acres of land is entered), displays appropriate warnings.

The following values are used for control (some of them are hidden from the player, he must determine them himself):

- Land sales and purchases are made at the current price
- Each inhabitant consumes 20 bushels of wheat per year
- Each resident can cultivate a maximum of 10 acres of land
- Each acre requires 0.5 bushels of wheat per seed

Progress to the next round is determined by the rules:

- The amount of wheat harvested per acre is determined randomly from a range of 1 to 6
- Rats eat a random amount of wheat from the range from 0 to 0.07\*available number of bushels, including fees
- Each inhabitant consumes 20 bushels of wheat a day, those who lack food die of starvation
- If more than 45% of the population died of starvation during a round, the player immediately loses

The number of new arrivals is determined by the formula:
dead\_from\_famine /2 + (5 – collected\_from\_acre) \* bushels\_wheat / 600 + 1

then, if this number is less than 0, 0 is taken, if it is more than 50, then 50

- Plague occurs with a 15% probability, if it occurs, the population decreases by half with rounding down

After round 10, the game calculates the following statistics:

- Average annual percentage of starvation deaths P
- Number of acres of land per inhabitant L

and gives the player a score based on the results of the board:

- If P > 33% and L < 7-bad ("Because of your incompetence in management, the people staged a riot and drove you out of the city. Now you are forced to eke out a miserable existence in exile")
- If P > 10% and L < 9-is satisfactory ("You ruled with an iron hand, like Nero and Ivan the Terrible. The people breathed a sigh of relief, and no one wants to see you as ruler anymore")
- If P > 3% and L < 10-good ("You did quite well, of course, you have detractors, but many would like to see you at the head of the city again")
- Otherwise-excellent ("Fantastic! Charlemagne, Disraeli, and Jefferson couldn't have done better together.")
