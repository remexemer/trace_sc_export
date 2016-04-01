#include <systemc>
using namespace sc_core; 
    
//Assume that the type of PPA is sc_export<sc_signal_inout_if<int> >!
void sc_trace( sc_trace_file* tf, const sc_export<sc_signal_inout_if<int> > & exp, const std::string& name )
{
  if( tf ) {
    sc_trace( tf, (DCAST<const sc_signal_in_if<int>*>( exp.get_interface() ))->read(), name ); 
  }
}

class A: public sc_module
{
public:
	SC_HAS_PROCESS( A );
	A( sc_module_name n ): sc_module( n )
  {
    exp( sig ); 

    SC_THREAD( run ); 
    
  }

  ~A()
  {
  }

  void run()
  {
    sig.write( 0 ); 
    wait( 1, SC_NS ); 
    sig.write( 1 ); 
    wait( 1, SC_NS ); 
    sig.write( 2 ); 
    sc_stop();
  }
  
  sc_export<sc_signal_inout_if<int> > exp; 
private:
  sc_signal<int> sig; 
};

class Top: public sc_module
{
public:
	SC_HAS_PROCESS( Top );
	Top( sc_module_name n ): sc_module( n )
  {
    tf = sc_create_vcd_trace_file( "tf" ); 
    
    a = new A( "dut" ); 
  }
  ~Top()
  {
    sc_close_vcd_trace_file( tf ); 
  }
    
  // NOTE: sc_trace must be after the port binding (exp( sig )); otherwise, the exp.get_interface() return NULL!
  // Thus, binding in constructor and tracing in end_of_elaboration() may be a good idea. 
  void end_of_elaboration()
  {
    //sc_trace( tf, (DCAST<const sc_signal_in_if<int>*>( a->exp.get_interface() ))->read(), "exp" ); 
    sc_trace( tf, a->exp, "a_exp" ); // this is the only one line which VPIP owner need to add in the top module. 
  }
private:
  sc_trace_file * tf;
  A* a; 
}; 

int sc_main(int argc, char* argv[])
{
  Top top("top"); 

  sc_start(); 

  return 0; 
}
