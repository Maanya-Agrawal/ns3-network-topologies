#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/netanim-module.h"
#include "ns3/mobility-module.h"

using namespace ns3;

int main ()
{
  NodeContainer nodes;
  nodes.Create (20);

  InternetStackHelper stack;
  stack.Install (nodes);

  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

  for (int i = 0; i < 19; i++)
  {
    p2p.Install (nodes.Get (i), nodes.Get (i+1));
  }

  MobilityHelper mobility;
  mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  mobility.Install(nodes);

  AnimationInterface anim("bus20.xml");

  for (int i = 0; i < 20; i++)
  {
    anim.SetConstantPosition(nodes.Get(i), 10*i, 50);
  }

  Simulator::Stop (Seconds (5));
  Simulator::Run ();
  Simulator::Destroy ();
}

