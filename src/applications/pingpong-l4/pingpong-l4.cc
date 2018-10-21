/* A RapidNet application. Generated by RapidNet compiler. */

#include "pingpong-l4.h"
#include <cstdlib>
#include "ns3/nstime.h"
#include "ns3/simulator.h"
#include "ns3/type-ids.h"
#include "ns3/rapidnet-types.h"
#include "ns3/rapidnet-utils.h"
#include "ns3/assignor.h"
#include "ns3/selector.h"
#include "ns3/rapidnet-functions.h"

using namespace std;
using namespace ns3;
using namespace ns3::rapidnet;
using namespace ns3::rapidnet::pingpongl4;

const string PingpongL4::EPING = "ePing";
const string PingpongL4::EPINGPONGFINISH = "ePingPongFinish";
const string PingpongL4::EPONG = "ePong";
const string PingpongL4::TLINK = "tLink";

NS_LOG_COMPONENT_DEFINE ("PingpongL4");
NS_OBJECT_ENSURE_REGISTERED (PingpongL4);

TypeId
PingpongL4::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::rapidnet::pingpongl4::PingpongL4")
    .SetParent<RapidNetApplicationBase> ()
    .AddConstructor<PingpongL4> ()
    ;
  return tid;
}

PingpongL4::PingpongL4()
{
  NS_LOG_FUNCTION_NOARGS ();
}

PingpongL4::~PingpongL4()
{
  NS_LOG_FUNCTION_NOARGS ();
}

void
PingpongL4::DoDispose (void)
{
  NS_LOG_FUNCTION_NOARGS ();

  RapidNetApplicationBase::DoDispose ();
}

void
PingpongL4::StartApplication (void)
{
  NS_LOG_FUNCTION_NOARGS ();

  RapidNetApplicationBase::StartApplication ();
  RAPIDNET_LOG_INFO("PingpongL4 Application Started");
}

void
PingpongL4::StopApplication ()
{
  NS_LOG_FUNCTION_NOARGS ();

  RapidNetApplicationBase::StopApplication ();
  RAPIDNET_LOG_INFO("PingpongL4 Application Stopped");
}

void
PingpongL4::InitDatabase ()
{
  //RapidNetApplicationBase::InitDatabase ();

  AddRelationWithKeys (TLINK, attrdeflist (
    attrdef ("tLink_attr1", IPV4),
    attrdef ("tLink_attr2", IPV4)));

}

void
PingpongL4::DemuxRecv (Ptr<Tuple> tuple)
{
  RapidNetApplicationBase::DemuxRecv (tuple);

  if (IsInsertEvent (tuple, TLINK))
    {
      R1Eca0Ins (tuple);
    }
  if (IsRecvEvent (tuple, EPING))
    {
      R2_eca (tuple);
    }
  if (IsRecvEvent (tuple, EPONG))
    {
      R3_eca (tuple);
    }
}

void
PingpongL4::R1Eca0Ins (Ptr<Tuple> tLink)
{
  RAPIDNET_LOG_INFO ("R1Eca0Ins triggered");

  Ptr<Tuple> result = tLink;

  result = result->Project (
    EPING,
    strlist ("tLink_attr2",
      "tLink_attr1",
      "tLink_attr2"),
    strlist ("ePing_attr1",
      "ePing_attr2",
      RN_DEST));

  Send (result);
}

void
PingpongL4::R2_eca (Ptr<Tuple> ePing)
{
  RAPIDNET_LOG_INFO ("R2_eca triggered");

  Ptr<Tuple> result = ePing;

  result = result->Project (
    EPONG,
    strlist ("ePing_attr2",
      "ePing_attr1",
      "ePing_attr2"),
    strlist ("ePong_attr1",
      "ePong_attr2",
      RN_DEST));

  Send (result);
}

void
PingpongL4::R3_eca (Ptr<Tuple> ePong)
{
  RAPIDNET_LOG_INFO ("R3_eca triggered");

  Ptr<Tuple> result = ePong;

  result = result->Project (
    EPINGPONGFINISH,
    strlist ("ePong_attr1"),
    strlist ("ePingPongFinish_attr1"));

  SendLocal (result);
}

