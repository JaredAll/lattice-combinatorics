#include <cstdint>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

struct Ball_data
{
    bool use_ball;
    bool use_double;
    bool prev_use_ball;
    bool prev_use_double;
    //bool first_pos_ball;
    //bool first_pos_double;
};

struct Sequence_data
{
    uint bonds_made;
    uint num_balls_used;
    uint num_doubles_used;
    Ball_data ball_info;
    uint lattice_length;
    string sequence;
};

struct Sequence_bounds
{
    uint length;
    uint num_bonds;
    uint num_balls;
    uint num_doubly_occ;
};

/* A function to determine the number of sequences of balls that bind when 
 * adjacent to each other given a certain length, red ball number, green ball 
 * number, doubly occupied position number, and bond number, through branching 
 * and bounding.
 * @param this_sequence the current sequence data
 * @param sequences the collection of complete sequences
 * @param bounds the current bounds for the sequence
 */
void branch_bound( Sequence_data this_sequence, vector< Sequence_data >
                   & sequences, Sequence_bounds & bounds );

int main()
{    
    Sequence_data empty_lattice = { 0, 0, 0, { false, false,
                                               false, false }, 0, "" };
    Sequence_bounds bounds;

    ifstream file;
    file.open("two_ball_bounds_N_D.txt");
    file >> bounds.num_bonds;
    file >> bounds.num_balls;
    file >> bounds.num_doubly_occ;
    file >> bounds.length;
    file.close();

    vector< Sequence_data > sequences;

    Sequence_data start_empty = empty_lattice;
    
    Sequence_data start_ball = empty_lattice;
    start_ball.ball_info.use_ball = true;
    //start_ball.ball_info.first_pos_ball = true;
    
    Sequence_data start_double = empty_lattice;
    start_double.ball_info.use_double = true;
    //start_double.ball_info.first_pos_double = true;


    if( bounds.num_balls <= 2 * bounds.length && bounds.num_doubly_occ <= 2 *
        bounds.num_balls )
    {
        
        branch_bound( start_empty, sequences, bounds );
        branch_bound( start_ball, sequences, bounds );
        branch_bound( start_double, sequences, bounds );
        
        /* if( sequences.size() > 0 )
        {
            cout << endl;
            cout << "These are the sequences with " << bonds <<
                " bonds: " << endl;
              
            for( uint i = 0; i < sequences.size(); i++ )
            {
                cout << sequences.at( i ).sequence << endl;
            }
            
            total_sequences += sequences.size();
            cout << bounds.num_bonds << " " << bounds.num_balls
                 << " " << bounds.num_doubly_occ << " " << bounds.length
                 << total_sequences << endl;
                 }*/

        if( sequences.size() > 0 )
        {
            cout << bounds.num_bonds << " " << bounds.num_balls
                 << " " << bounds.num_doubly_occ << " " << bounds.length << " "
                 << sequences.size() << endl;
        }
    }

    /*cout << "The total number of generated sequences is " <<
        total_sequences << endl;
     if( check_total == total_sequences )
    {
        cout << "This matches the prediction." << endl;
    }
    else
    {
        cout << "This fails to match the prediction." << endl;
        }*/

}

void branch_bound( Sequence_data this_sequence, vector< Sequence_data >
                   & sequences, Sequence_bounds & bounds )
{
    //increment position in lattice
    this_sequence.lattice_length++;

    
    //check for bonds
    if( this_sequence.ball_info.use_ball &&
        this_sequence.ball_info.prev_use_ball )
    {
        this_sequence.bonds_made++;
    }

    if( this_sequence.ball_info.use_ball &&
        this_sequence.ball_info.prev_use_double )
    {
        this_sequence.bonds_made += 2;
    }

    if( this_sequence.ball_info.use_double &&
        this_sequence.ball_info.prev_use_ball )
    {
        this_sequence.bonds_made += 2;
    }
    
    if( this_sequence.ball_info.use_double &&
        this_sequence.ball_info.prev_use_double )
    {
        this_sequence.bonds_made += 4;
    }

    /*if( this_sequence.lattice_length == bounds.length )
    {
            if( this_sequence.ball_info.use_ball &&
                this_sequence.ball_info.first_pos_ball )
            {
                this_sequence.bonds_made++;
            }

            if( this_sequence.ball_info.use_ball &&
                this_sequence.ball_info.first_pos_double )
            {
                this_sequence.bonds_made += 2;
            }
            
            if( this_sequence.ball_info.use_double &&
                this_sequence.ball_info.first_pos_ball )
            {
                this_sequence.bonds_made += 2;
            }
            
            if( this_sequence.ball_info.use_double &&
                this_sequence.ball_info.first_pos_double )
            {
                this_sequence.bonds_made += 4;
            }
            }*/

    
    //check for use of balls and update sequence
    if( this_sequence.ball_info.use_ball )
    {
        this_sequence.num_balls_used++;
        this_sequence.sequence = this_sequence.sequence + "B";
        this_sequence.ball_info.prev_use_ball = true;
        this_sequence.ball_info.prev_use_double = false;
    }
    else if( this_sequence.ball_info.use_double )
    {
        this_sequence.num_balls_used += 2;
        this_sequence.num_doubles_used++;
        this_sequence.sequence = this_sequence.sequence + "D";
        this_sequence.ball_info.prev_use_double = true;
        this_sequence.ball_info.prev_use_ball = false;
    }
    else
    {
        this_sequence.sequence = this_sequence.sequence + "E";
        this_sequence.ball_info.prev_use_ball = false;
        this_sequence.ball_info.prev_use_double = false;
    }

    
    //bound if necessary
    //uint balls_remaining = bounds.num_red_balls + bounds.num_green_balls -
    //( this_sequence.num_red_balls_used + this_sequence.num_green_balls_used );
    uint lat_remaining = bounds.length - this_sequence.lattice_length;

    //checks for lattice space
    if( lat_remaining > bounds.length )
    {
        
        /*cout << "no more space for: " <<
          this_sequence.sequence << " " << bounds.length << endl;*/
        return;
    }
    
    //checks for too many balls
    if( this_sequence.num_balls_used > bounds.num_balls )
    {
        
        /*cout << "too many balls for: " <<
          this_sequence.sequence << " " << bounds.num_balls << endl;*/
        return;
    }

    //checks for too many bonds
    if( this_sequence.bonds_made > bounds.num_bonds )
    {
        
        /*cout << "too many bonds for: " <<
            this_sequence.sequence << " " << lat_remaining << bounds.length
            << endl;*/
        return;
    }

    /*
    cout << "current bonds: " << this_sequence.bonds_made << endl;
    cout << "current balls: " << this_sequence.num_balls_used << endl;
    cout << "current length: " << this_sequence.lattice_length << endl;
    cout << endl;*/
    
    if( this_sequence.lattice_length == bounds.length
        && this_sequence.bonds_made == bounds.num_bonds
        && this_sequence.num_balls_used == bounds.num_balls
        && this_sequence.num_doubles_used == bounds.num_doubly_occ )
    {
        sequences.push_back( this_sequence );
        return;
    }

    //prepare conditions for next entry in sequence
    Sequence_data next_empty = this_sequence;
    next_empty.ball_info.use_ball = false;
    next_empty.ball_info.use_double = false;

    Sequence_data next_ball = this_sequence;
    next_ball.ball_info.use_ball = true;
    next_ball.ball_info.use_double = false;

    Sequence_data next_double = this_sequence;
    next_double.ball_info.use_ball = false;
    next_double.ball_info.use_double = true;

    branch_bound( next_ball, sequences, bounds );
    branch_bound( next_double, sequences, bounds );
    branch_bound( next_empty, sequences, bounds );
}
