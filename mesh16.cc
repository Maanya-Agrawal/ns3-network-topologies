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
  nodes.Create (16);   // 16 nodes

  InternetStackHelper stack;
  stack.Install (nodes);

  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

  // -------- Full Mesh Connections --------
  for (int i = 0; i < 16; i++)
  {
    for (int j = i+1; j < 16; j++)
    {
      p2p.Install (nodes.Get(i), nodes.Get(j));
    }
  }

  // -------- Mobility --------
  MobilityHelper mobility;
  mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  mobility.Install(nodes);

  AnimationInterface anim("mesh16.xml");

  // -------- Clean 4x4 Grid Layout --------
  int index = 0;
  for (int row = 0; row < 4; row++)
  {
    for (int col = 0; col < 4; col++)
    {
      anim.SetConstantPosition(nodes.Get(index), 20 + col*20, 20 + row*20);
      index++;
    }
  }

  Simulator::Stop (Seconds(5));
  Simulator::Run ();
  Simulator::Destroy ();
}

