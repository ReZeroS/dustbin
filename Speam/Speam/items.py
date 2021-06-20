# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# https://doc.scrapy.org/en/latest/topics/items.html

import scrapy


class SpeamItem(scrapy.Item):
    # define the fields for your item here like:
    pass

class SteamItem(scrapy.Item):

    collection = table = "game"

    id = scrapy.Field()
    title = scrapy.Field()
    url = scrapy.Field()
    release_date = scrapy.Field()
    rencent_responsive = scrapy.Field()
    summary_responsive = scrapy.Field()
    player_count = scrapy.Field()
    tags = scrapy.Field()
    system = scrapy.Field()
    officials = scrapy.Field()

