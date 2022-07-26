// void	Command::replyAllReachable(std::string message)
// {
// 	std::vector<Channel*> channels(_invoker->getChannels());
// 	userVec	uniqueUser;

// 	for (channelIterator it = channels.begin(); it != channels.end(); it++)
// 	{
// 		userVec channelUser = (*it)->getMembers();
// 		userVec merged;
// 		std::sort(channelUser.begin(), channelUser.end());
// 		std::merge(uniqueUser.begin(), uniqueUser.end(), 
// 			channelUser.begin(), channelUser.end(), std::back_inserter(merged));
// 		userVec::iterator dupesIt = std::unique(merged.begin(), merged.end());
// 		merged.erase(dupesIt, merged.end());
// 		uniqueUser = merged;
// 	}
// 	for (userVec::iterator it = uniqueUser.begin(); it != uniqueUser.end(); it++)
// 		if (*it != _invoker)
// 			(*it)->addReply(message);
// }