import scrapy
from scrapy import Selector, Request

from Speam.items import SteamItem
from Speam.util.generate import get_md5


class SteamSpider(scrapy.Spider):
    name = "steam"
    allowed_domains = ['steampowered.com']

    cookie = {
        'browserid': '',
        'sessionid': '',
        'timezoneOffset': '',
        '_ga': '',
        '_gid': '',
        'Steam_Language': 'english',
        'steamMachineAuth76561198294886228': '',
        'steamLoginSecure': '',
        'steamRememberLogin': '',
        'app_impressions': '',
        'birthtime': '',
        'lastagecheckage': '',
        'recentapps': '',
        'review_beta_enabled': '',
        'review_purchase_type_filter': ''
    }

    def start_requests(self):
        base_url = 'https://store.steampowered.com/search/?page='
        urls = [
            base_url + str(i)
            for i in range(1, 1996)
        ]
        for url in urls:
            yield scrapy.Request(url=url, cookies=self.cookie, callback=self.parse)

    def parse(self, response):
        document = Selector(response)

        links = document.xpath("//div[@id='search_result_container']/div[2]//@href").extract()
        for link in links:
            yield Request(url=link, cookies=self.cookie, callback=self.parse_detail)

    def parse_detail(self, response):
        detail = Selector(response)
        title = detail.xpath("//div[@class='apphub_AppName']/text()").extract_first("")
        url = detail.xpath("//div[@class='block_content_inner']/div[2]/a/@href").extract_first("")
        release_date = detail.xpath("//*[@id='game_highlights']/div[1]/div/div[3]/div/div[3]/div[2]/text()").extract_first("")
        rencent_responsive = detail.xpath("//div[@class='summary column']/span[3]/text()").extract_first("").strip()
        summary_responsive = detail.xpath(
            "//*[@id='game_highlights']/div[1]/div/div[3]/div/div[1]/div[2]/span[1]/text()").extract_first("")
        player_count = detail.xpath("//*[@id='reviews_filter_options']/div[2]/div[2]/div/label[1]/span/text()").extract_first("")[2:-1]


        tags = detail.xpath("//div[@class='glance_tags popular_tags']/a")
        user_tags = []
        for single_tag in tags:
            t = single_tag.xpath('text()').extract_first("").strip()
            user_tags.append(t)
        system = []
        systems = detail.xpath("//div[@class='sysreq_tabs']/div")
        for sy in systems:
            s = sy.xpath("text()").extract_first("").strip()
            system.append(s)
        dev_urls = detail.xpath("//div[@class='block_content_inner']/div/div[@class='dev_row']")
        officials = {}
        for dev_url in dev_urls:
            key = dev_url.xpath("./b/text()").extract_first("")[:-1]
            value = dev_url.xpath(".//@href").extract_first("")
            officials[key] = value


        # system = system_format(system)
        id = get_md5(url)

        steamItem = SteamItem()
        steamItem['id'] = id
        steamItem['title'] = title
        steamItem['url'] = url
        steamItem['release_date'] = release_date
        steamItem['rencent_responsive'] = rencent_responsive
        steamItem['summary_responsive'] = summary_responsive
        steamItem['player_count'] = player_count
        steamItem['tags'] = user_tags
        steamItem['system'] = system
        steamItem['officials'] = officials

        yield steamItem
