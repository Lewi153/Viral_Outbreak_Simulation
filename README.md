# Viral_Outbreak_Simulation
Simplified simulation of the outbreak of a highly transmissible virus (hemorrhagic smallpox) within a small community. 

This is a simplified simulation of a viral outbreak using data from: 'International Journal of Infectious Diseases' (2007) 11, 98—108 The goal of this project is to estimate the transmission rate of an incurable, highly transmissible virus. Hemorrhagic smallpox was chosen for this simulation as it has the highest efficacy rate of the three in the research paper.

We begin by setting up a small community containing various mixing groups (ie schools, workplaces, families, etc.) A population is then created, and all persons are randomly placed in these groups based on age and average size of the group type. An individual group is then chosen and exposed to the virus. The probabilities of infection for each person in the population is then calculated based on the health status of people in each of their personal mixing groups. The simulation is run for a user-defined number of days. The health status of all persons at the end of each day is placed in a text file: Output.txt
