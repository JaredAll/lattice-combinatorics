#include <cstdint>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

struct Sequence_data
{
    uint bonds_made;
    uint num_balls_used;
    uint lattice_length;
    string sequence;
};

struct Sequence_bounds
{
    uint length;
    uint num_bonds;
    uint num_balls;
};

/* A function to determine the number of sequences of balls that bind when 
 * adjacent to each other given a certain length, ball number, and bond number, 
 * through branching and bounding.
 * @param this_sequence the current sequence
 * @param sequences the collection of complete sequences
 * @param bounds the current bounds for the sequence
 * @param use_ball true to use ball false to not use ball in this position
 * @param prev_use_ball does the previous position contain a ball
 */
void branch_bound( Sequence_data this_sequence, vector< Sequence_data > & sequences, Sequence_bounds & bounds, bool use_ball, bool prev_use_ball );

int main()
{    
    Sequence_data empty_lattice = { 0, 0, 0, "" };
    Sequence_bounds bounds;

    ifstream file;
    file.open("bounds.txt");
    file >> bounds.num_balls;
    file >> bounds.length;
    file >> bounds.num_bonds;
    file.close();

    //uint num_sequences = 0;
    vector< Sequence_data > sequences;

    branch_bound( empty_lattice, sequences, bounds, true, false );
    branch_bound( empty_lattice, sequences, bounds, false, false );

    cout << "These are the sequences: " << endl;

    for( uint i = 0; i < sequences.size(); i++ )
    {
        cout << sequences.at( i ).sequence << endl;
    }

    cout << "The number of such sequences is " << sequences.size() << endl;

}

/* A function to determine the number of sequences of balls that bind when 
 * adjacent to each other given a certain length, ball number, and bond number, 
 * through branching and bounding.
 * @param this_sequence the current sequence
 * @param sequences the collection of complete sequences
 * @param bounds the current bounds for the sequence
 * @param use_ball true to use ball false to not use ball in this position
 * @param prev_use_ball does the previous position contain a ball
 * @author Jared Allen
 */
void branch_bound( Sequence_data this_sequence, vector< Sequence_data > & sequences, Sequence_bounds & bounds, bool use_ball, bool prev_use_ball )
{
    //increment position in lattice
    this_sequence.lattice_length++;

    //check for bond
    if( use_ball && prev_use_ball )
    {
        this_sequence.bonds_made++;
    }

    //check for use of ball and update sequence
    if( use_ball )
    {
        this_sequence.num_balls_used++;
        this_sequence.sequence = this_sequence.sequence + "B";
        prev_use_ball = true;
    }
    else
    {
        this_sequence.sequence = this_sequence.sequence + "E";
        prev_use_ball = false;
    }

    //bound if necessary
    uint balls_remaining = bounds.num_balls - this_sequence.num_balls_used;
    uint lat_remaining = bounds.length - this_sequence.lattice_length;
    //uint bonds_remaining = bounds.num_bonds - this_sequence.bonds_made;
    //uint bond_space = 2 * bonds_remaining;

    //checks for lattice space
    if( lat_remaining > bounds.length )
    {
        /*
        cout << "no more space for: " <<
            this_sequence.sequence << " " << endl;
            cout << endl;*/
        return;
    }
    
    //checks for too many balls
    if( this_sequence.num_balls_used > bounds.num_balls )
    {
        /*
        cout << "too many balls for: " <<
            this_sequence.sequence << " " << bounds.num_balls << endl;
            cout << endl;*/
        return;
    }

    //checks for space for balls
    if( balls_remaining > lat_remaining )
    {
        /*
        cout << "no ball space for: " <<
        this_sequence.sequence << " " << lat_remaining << endl;*/
        return;
    }

    /*
    //checks for space for bonds
    if( !prev_use_ball && bond_space > lat_remaining )
    {
        cout << "no bond space for: " <<
            this_sequence.sequence << " " << lat_remaining << endl;
        cout << endl;
        return;    
    }

    
    //checks for balls for bonds
    if( !prev_use_ball && bond_space > balls_remaining )
    {
        cout << "insufficient balls for bonds for : " <<
            this_sequence.sequence << " " << lat_remaining << endl;
        cout << endl;
        return;
    }
    */

    //checks for too many bonds
    if( this_sequence.bonds_made > bounds.num_bonds )
    {
        /*
        cout << "too many bonds for: " <<
            this_sequence.sequence << " " << lat_remaining << endl;
            cout << endl;*/
        return;
    }

    /*
    cout << "current bonds: " << this_sequence.bonds_made << endl;
    cout << "current balls: " << this_sequence.num_balls_used << endl;
    cout << "current length: " << this_sequence.lattice_length << endl;
    cout << endl;*/
    
    if( this_sequence.lattice_length == bounds.length
        && this_sequence.bonds_made == bounds.num_bonds
        && this_sequence.num_balls_used == bounds.num_balls)
    {
        sequences.push_back( this_sequence );
        return;
    }
    
    branch_bound( this_sequence, sequences, bounds, true, prev_use_ball );
    branch_bound( this_sequence, sequences, bounds, false, prev_use_ball );
}
