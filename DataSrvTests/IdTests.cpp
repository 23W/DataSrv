#include "pch.h"
#include "Storage/Data Model/Id.h"

TEST(Id, UniqueId)
{
    const auto id1 = Id::MakeNew();
    const auto id2 = Id::MakeNew();

    EXPECT_NE(id1, id2);
}

TEST(Id, Copyable)
{
    const auto id1 = Id::MakeNew();
    const auto id2 = id1;
    const auto id3 = Id{ id1 };

    EXPECT_EQ(id1, id2);
    EXPECT_EQ(id2, id3);
}

TEST(Id, GUID)
{
    auto guid1 = GUID_NULL;
    ASSERT_HRESULT_SUCCEEDED(CoCreateGuid(&guid1));

    const auto id1 = Id(guid1);
    const auto id2 = Id(guid1);

    auto guid2 = id2.operator GUID();

    EXPECT_EQ(id1, id2);
    EXPECT_EQ(guid1, guid2);
}

TEST(Id, string)
{
    const auto id1 = Id::MakeNew();
    const auto sId1 = id1.operator std::string();
    const auto sId2 = id1.operator std::string();
    const auto id2 = Id{ sId2 };

    EXPECT_EQ(sId1, sId2);
    EXPECT_EQ(id1, id2);
}
