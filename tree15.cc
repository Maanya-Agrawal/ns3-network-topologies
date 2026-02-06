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
  nodes.Create (15);   // 15 nodes

  InternetStackHelper stack;
  stack.Install (nodes);

  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

  // Create perfect binary tree connections
  for (int i = 0; i < 7; i++)
  {
    p2p.Install (nodes.Get(i), nodes.Get(2*i+1));
    p2p.Install (nodes.Get(i), nodes.Get(2*i+2));
  }

  // Mobility
  MobilityHelper mobility;
  mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  mobility.Install(nodes);

  AnimationInterface anim("tree15.xml");

  // ---- Positioning (Clean Levels) ----

  // Level 0 (Root)
  anim.SetConstantPosition(nodes.Get(0), 50, 10);

  // Level 1
  anim.SetConstantPosition(nodes.Get(1), 30, 25);
  anim.SetConstantPosition(nodes.Get(2), 70, 25);

  // Level 2
  anim.SetConstantPosition(nodes.Get(3), 20, 45);
  anim.SetConstantPosition(nodes.Get(4), 40, 45);
  anim.SetConstantPosition(nodes.Get(5), 60, 45);
  anim.SetConstantPosition(nodes.Get(6), 80, 45);

  // Level 3
  anim.SetConstantPosition(nodes.Get(7), 10, 70);
  anim.SetConstantPosition(nodes.Get(8), 25, 70);
  anim.SetConstantPosition(nodes.Get(9), 35, 70);
  anim.SetConstantPosition(nodes.Get(10), 45, 70);
  anim.SetConstantPosition(nodes.Get(11), 55, 70);
  anim.SetConstantPosition(nodes.Get(12), 65, 70);
  anim.SetConstantPosition(nodes.Get(13), 75, 70);
  anim.SetConstantPosition(nodes.Get(14), 90, 70);

  Simulator::Stop (Seconds(5));
  Simulator::Run ();
  Simulator::Destroy ();
}

