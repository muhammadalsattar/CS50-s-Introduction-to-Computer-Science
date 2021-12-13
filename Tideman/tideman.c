#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];



int pair_count;
int candidate_count;

int source;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
int winner(int x);
bool chain(int x, int y);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Checking for valid candidate name
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int index = 0;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] != preferences[j][i])
            {
                // Updating pairs and count if 2 candidates arent tied
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[index].winner = i;
                    pairs[index].loser = j;
                    pair_count += 1;
                    index += 1;
                }
                else if (preferences[j][i] > preferences[i][j])
                {
                    pairs[index].winner = j;
                    pairs[index].loser = i;
                    pair_count += 1;
                    index += 1;
                }
            }

        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                pair temp;
                temp.winner = pairs[i].winner;
                temp.loser = pairs[i].loser;

                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;

                pairs[j].winner = temp.winner;
                pairs[j].loser = temp.loser;
            }
        }
    }
}

// function to return number of wins for every candidate
int winner(int x)
{
    int count = 0;
    int num;
    for (int i = 0; i < pair_count; i++)
    {
        if (pairs[i].winner == x && locked[pairs[i].winner][pairs[i].loser])
        {
            num = pairs[i].loser;
            count += 1;
        }
    }
    // returning loser in case winner has only 1 win.
    if (count == 1)
    {
        return num;
    }
    // returning -1 in case candidate has no wins
    else if (count == 0)
    {
        return -1;
    }
    return -2;
}

// function to figure out whether locking a pair would create a cycle
bool chain(int x, int y)
{
    if (x == winner(y))
    {
        return true;
    }
    if (winner(y) == -2)
    {
        return true;
    }
    else if (winner(y) == -1)
    {
        return false;
    }
    return chain(x, winner(y));
}

// locking non-cycle pairs
void lock_pairs(void)
{
    printf("\n");
    
    for (int i = 0; i < pair_count; i++)
    {
        if (!chain(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    
    int candidate[candidate_count];
   
    for (int i = 0; i < candidate_count; i++)
    {
        candidate[i] = 0;
    }
   
    for (int j = 0; j < candidate_count; j++)
    {
        for (int k = 0; k < candidate_count; k++)
        {
            if (locked[j][k])
            {
                candidate[k] += 1;
            }
        }
    }
    // Getting the source of the graph who has no arrows pointing at him.
    for (int r = 0; r < candidate_count; r++)
    {
        if (candidate[r] == 0)
        {
            source = r;
            break;
        }
    }
   
    printf("%s\n", candidates[source]);
}