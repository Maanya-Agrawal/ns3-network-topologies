#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main ()
{
  NodeContainer hub;
  hub.Create (1);

  NodeContainer spokes;
  spokes.Create (15);

  InternetStackHelper stack;
  stack.Install (hub);
  stack.Install (spokes);

  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

  for (int i = 0; i < 15; i++)
  {
    NodeContainer pair (hub.Get (0), spokes.Get (i));
    p2p.Install (pair);
  }

  AnimationInterface anim ("star16.xml");

  Simulator::Stop (Seconds (5));
  Simulator::Run ();
  Simulator::Destroy ();
}

